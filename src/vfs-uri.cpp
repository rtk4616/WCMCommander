/*
 * Part of Wal Commander GitHub Edition
 * https://github.com/corporateshark/WalCommander
 * walcommander@linderdaum.com
 */

#ifdef _WIN32
#  include <winsock2.h>
#endif

#include "vfs-uri.h"
#include "vfs-smb.h"
#include "vfs-ftp.h"
#include "vfs-sftp.h"
#include "vfs-tmp.h"
#include "string-util.h"
#include "urlparser/LUrlParser.h"

static unicode_t rootPathStr[] = {'/', 0};

inline const unicode_t* FindFirstChar( const unicode_t* s, unicode_t c )
{
	for ( ; *s; s++ ) if ( *s == c ) { return s; }

	return s;
}

#ifdef LIBSMBCLIENT_EXIST

static void SetString( char* dest, int len, const char* src )
{
	for ( ; *src && len > 1; dest++, src++, len-- ) { *dest = *src; }

	if ( len > 0 ) { *dest = 0; }
}

clPtr<FS> ParzeSmbURI( const unicode_t* uri, FSPath& path, clPtr<FS>* checkFS, int count )
{
	path.Set( rootPathStr );

	if ( !uri[0] ) { return new FSSmb(); }

	FSSmbParam param;

	const unicode_t* userDelimiter = FindFirstChar( uri, '@' );

	if ( *userDelimiter )
	{
		FSString s( CS_UNICODE, uri, userDelimiter - uri );
		SetString( const_cast<char*>( param.user ), sizeof( param.user ), s.GetUtf8() );
		uri = userDelimiter + 1;
	}

	const unicode_t* hostEnd = FindFirstChar( uri, '/' );
	FSString host( CS_UNICODE, uri, hostEnd - uri );
	SetString( const_cast<char*>( param.server ), sizeof( param.server ), host.GetUtf8() );

	uri = hostEnd;

	FSString link = uri;

	if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

	return new FSSmb( &param );
}

#endif

clPtr<FS> ParzeFtpURI( const unicode_t* uri, FSPath& path, clPtr<FS>* checkFS, int count )
{
	path.Set( rootPathStr );

	if ( !uri[0] ) { return clPtr<FS>(); }

	FSFtpParam param;

	LUrlParser::clParseURL URL = LUrlParser::clParseURL::ParseURL( unicode_to_utf8_string( uri ) );

	if ( !URL.IsValid() ) return clPtr<FS>();
	
	param.user = URL.m_UserName;
	param.pass = URL.m_Password;
	param.anonymous = param.user.empty();
	param.server = std::string( URL.m_Host );

	URL.GetPort( &param.port );

	std::vector<unicode_t> Path = utf8str_to_unicode( URL.m_Path );

	FSString link = Path.data();

	if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

	for ( int i = 0; i < count; i++ )
	{
		if ( checkFS[i].Ptr() && checkFS[i]->Type() == FS::FTP )
		{
			FSFtp* p = ( FSFtp* )checkFS[i].Ptr();
			FSFtpParam checkParam;
			p->GetParam( &checkParam );

			if ( param.server == checkParam.server &&
			     ( param.anonymous == checkParam.anonymous && ( param.anonymous || (param.user == checkParam.user) ) ) &&
			     param.port == checkParam.port )
			{
				return checkFS[i];
			}
		}
	}

	return new FSFtp( &param );
}

#if defined(LIBSSH_EXIST) || defined(LIBSSH2_EXIST)

clPtr<FS> ParzeSftpURI( const unicode_t* uri, FSPath& path, clPtr<FS>* checkFS, int count )
{
	path.Set( rootPathStr );

	if ( !uri[0] ) { return clPtr<FS>(); }

	FSSftpParam param;

	LUrlParser::clParseURL URL = LUrlParser::clParseURL::ParseURL( unicode_to_utf8_string(uri) );

	if ( !URL.IsValid())  return clPtr<FS>();

	param.user = URL.m_UserName;
	param.server = URL.m_Host;

	URL.GetPort( &param.port );

	std::vector<unicode_t> Path = utf8str_to_unicode( URL.m_Path );

	FSString link = Path.data();

	if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

	for ( int i = 0; i < count; i++ )
	{
		if ( checkFS[i].Ptr() && checkFS[i]->Type() == FS::SFTP )
		{
			FSSftp* p = ( FSSftp* )checkFS[i].Ptr();
			FSSftpParam checkParam;

			p->GetParam( &checkParam );

			if ( param.server == checkParam.server && param.user == checkParam.user && param.port == checkParam.port )
			{
				return checkFS[i];
			}
		}
	}

	return new FSSftp( &param );
}

#endif

clPtr<FS> ParzeURI( const unicode_t* uri, FSPath& path, clPtr<FS>* checkFS, int count )
{

#ifdef LIBSMBCLIENT_EXIST

	if ( uri[0] == 's' && uri[1] == 'm' && uri[2] == 'b' && uri[3] == ':' && uri[4] == '/' && uri[5] == '/' )
	{
		return ParzeSmbURI( uri + 6, path, checkFS, count );
	}

#endif

	if ( uri[0] == 'f' && uri[1] == 't' && uri[2] == 'p' && uri[3] == ':' && uri[4] == '/' && uri[5] == '/' )
	{
		return ParzeFtpURI( uri, path, checkFS, count );
	}

#if defined(LIBSSH_EXIST) || defined(LIBSSH2_EXIST)

	if ( uri[0] == 's' && uri[1] == 'f' && uri[2] == 't' && uri[3] == 'p' && uri[4] == ':' && uri[5] == '/' && uri[6] == '/' )
	{
		return ParzeSftpURI( uri + 7, path, checkFS, count );
	}

#endif

	if (uri[0] == 't' && uri[1] == 'm' && uri[2] == 'p' && uri[3] == ':' && uri[4] == '/' && uri[5] == '/')
	{
		clPtr<FS> baseFS = ParzeURI(uri + 6, path, checkFS, count);
		return new FSTmp(baseFS);
	}

	if (uri[0] == 'f' && uri[1] == 'i' && uri[2] == 'l' && uri[3] == 'e' && uri[4] == ':' && uri[5] == '/' && uri[6] == '/')
	{
		uri += 6;   //оставляем 1 символ '/'
	}


#ifdef _WIN32
	int c = uri[0];

	if ( c == '\\' || c == '/' )
	{
		if ( uri[1] == '/' || uri[1] == '\\' )
		{
			FSString link = uri + 1;

			if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

			if ( path.Count() == 1 )
			{
				clPtr<FS> netFs = new FSWin32Net( 0 );
				path.Set( CS_UTF8, "/" );
				return netFs;
			}

			if ( path.Count() == 2 )
			{
				static unicode_t aa[] = {'\\', '\\', 0};
				std::vector<wchar_t> name = UnicodeToUtf16( carray_cat<unicode_t>( aa, path.GetItem( 1 )->GetUnicode() ).data() );

				NETRESOURCEW r;
				r.dwScope = RESOURCE_GLOBALNET;
				r.dwType = RESOURCETYPE_ANY;
				r.dwDisplayType = RESOURCEDISPLAYTYPE_GENERIC;
				r.dwUsage = RESOURCEUSAGE_CONTAINER;
				r.lpLocalName = 0;
				r.lpRemoteName = name.data();
				r.lpComment = 0;
				r.lpProvider = 0;

				clPtr<FS> netFs = new FSWin32Net( &r );
				path.Set( CS_UTF8, "/" );
				return netFs;
			}

			return new FSSys( -1 );
		}

		FSString link = uri;

		if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

		return ( count > 0 && !checkFS[0].IsNull() ) ? checkFS[0] : clPtr<FS>();
	}

	if ( c >= 'A' && c <= 'Z' ) { c = c - 'A' + 'a'; }

	if ( c < 'a' || c > 'z' || uri[1] != ':' || ( uri[2] != '/' && uri[2] != '\\' ) )
	{
		FSString link = uri;

		if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

		return ( count > 0 && !checkFS[0].IsNull() ) ? checkFS[0] : clPtr<FS>();
	}

	FSString link = uri + 2;

	if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

	return new FSSys( c - 'a' );
#else
	FSString link = uri;

	if ( !ParzeLink( path, link ) ) { return clPtr<FS>(); }

	if ( uri[0] != '/' )
	{
		return ( count > 0 && !checkFS[0].IsNull() ) ? checkFS[0] : clPtr<FS>();
	}

	return new FSSys(); //systemclPtr<FS>;
#endif
}


clPtr<FS> ParzeCurrentSystemURL( FSPath& path )
{
#ifdef _WIN32

	int drive = 3; //c:
	char buf[0x100];
	UINT l = GetSystemDirectory( buf, sizeof( buf ) );

	if ( l > 0 )
	{
		int c = buf[0];
		drive = ( c >= 'A' && c <= 'Z' ) ? c - 'A' : ( ( c >= 'a' && c <= 'z' ) ? c - 'a' : 3 );
	}

	path.Set( CS_UTF8, "/" );
	return new FSSys( drive );
#else
	int bufSize = 1024;
	std::vector<sys_char_t> buf( bufSize );

	while ( true )
	{
		if ( getcwd( buf.data(), bufSize ) )
		{
			break;
		}

		if ( errno != ERANGE )
		{
			throw_syserr( 0, "Botva" );
		}

		bufSize *= 2;
		buf.resize( bufSize );
	}

	path.Set( sys_charset_id, buf.data() );
	return new FSSys(); //systemclPtr<FS>;
#endif
}

