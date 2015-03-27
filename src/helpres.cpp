/*
 * Part of WCM Commander
 * https://github.com/corporateshark/WCMCommander
 * walcommander@linderdaum.com
 */

const char* helpData_main =
   "<v10>/n"
   "/c{<shead><sbold>http:////wcm.linderdaum.com/n}"
   "/c{<shead><sbold>https:////github.com//corporateshark//WCMCommander/n}"
   "/c{<shead><sbold>wcm/@linderdaum.com/n}"
   "<v5>/n"
   "/c{<shead>Main window help/n}"
   "/c{<shead>Keyboard reference /n}"
   "<v5>/n"
   "/c@t"
   "Help			@c /r {<sbold>F1} @n" "<v5>@n"
   "View			@c /r {<sbold>F3} @c (folder size)@c @n" "<v5>@n"
   "Edit			@c /r {<sbold>F4} @c @c  @n"
   "			@c /r {<sbold>Shift-F4} @c @c  @n" "<v5>@n"
   "Copy			@c /r {<sbold>F5} @n" "<v2>@n"
   "			@c /r {<sbold>Shift-F5} @n" "<v5>@n"
   "Rename or move		@c /r {<sbold>F6} @n" "<v2>@n"
   "			@c /r {<sbold>Shift-F6} @n" "<v5>@n"
   "Create new folder	@c /r {<sbold>F7} @n" "<v2>@n"
   "Delete			@c /r {<sbold>F8} @n" "<v2>@n"
   "Show menu bar		@c /r {<sbold>F9} @n" "<v2>@n"
   "Quit			@c /r {<sbold>F10} @n" "<v2>@n"
   "Search file		@c /r {<sbold>Shift-F7} @c (Alt-F7) @n" "<v2>@n"
   "Save config		@c /r {<sbold>Shift-F9} @c @n" "<v2>@n"
   "Set left panel DRIVE	@c /r {<sbold>Shift-F1} @c (Alt-F1) @n" "<v2>@n"
   "Set right panel DRIVE	@c /r {<sbold>Shift-F2} @c (Alt-F2) @n" "<v2>@n"
   "Equal panels		@c /r {<sbold>Ctrl-=} @c@n" "<v2>@n"
   "Folder shortcuts	@c /r {<sbold>Ctrl-D} @c@n" "<v2>@n"
   "Toggle info dialog	@c /r {<sbold>Ctrl-L} @c@n" "<v2>@n"
#if defined(_WIN32)
	"Adjust font size @c /r {<sbold>Ctrl-WheelUp, Ctrl+WheelDn} @c@n" "<v2>@n"
#endif
	"Folders history @c /r {<sbold>Alt-F12} @c@n" "<v2>@n"
	"Copy the full path of the currently selected item  @c /r {<sbold>Ctrl-Alt-Ins} @c Alt+Shift+Ins, Ctrl+Shift+P @n" "<v2>@n"
   "@e/n"
   "<v10>/n"
   "/c{<shead>Panel/n}"
   "<v5>/n"
   "/c@t"
   "Reread panel		@c /r {<sbold>Ctrl-R}	@n" "<v2>@n"
   "Select other panel	@c /r {<sbold>Tab}	@n" "<v2>@n"
   "Panel on//off		@c /r {<sbold>Ctrl-O }	@n" "<v2>@n"
   "Go to home directory	@c /r {<sbold>Ctrl ~ }	@n" "<v2>@n"
   "Go to filesystem root	@c /r {<sbold>Ctrl-// or Ctrl-\\ }@n" "<v2>@n"
   "Change panel mode	@c /r {<sbold>Ctrl-1 ... Ctrl-5} @n" "<v2>@n"
   "Sort by name		@c /r {<sbold>Ctrl-F3}	@n" "<v2>@n"
   "Sort by extension	@c /r {<sbold>Ctrl-F4}	@n" "<v2>@n"
   "Sort by time		@c /r {<sbold>Ctrl-F5}	@n" "<v2>@n"
   "Sort by size		@c /r {<sbold>Ctrl-F6}	@n" "<v2>@n"
   "No sort		@c /r {<sbold>Ctrl-F7}	@n" "<v2>@n"
   "Show hidden files (on//off)	@c /r {<sbold>Ctrl-H} @n" "<v2>@n"
   "Select(Unselect) current file	@c /r {<sbold>Ins} @n" "<v2>@n"
   "				@c /r {<sbold>Shift-Left//Right//Up//Down} @n" "<v2>@n"
   "Select group		@c /r {<sbold>GRAY +} @n" "<v2>@n"
   "Deselect group		@c /r {<sbold>GRAY -} @n" "<v2>@n"
   "Invert selection	@c /r {<sbold>GRAY *} @n" "<v2>@n"
   "Quick search		@c /r {<sbold>Alt /<symbol/>} @n"  " (Ctrl-Enter to next)<v2>@n"
	"Select files with the same extenstion @c /r {<sbold>Ctrl-GRAY +} @n" "<v2>@n"
	"Deselect files with the same extenstion @c /r {<sbold>Ctrl-GRAY -} @n" "<v2>@n"
   "@e/n"
   "<v10>/n"
   "/c{<shead>Command line/n}"
   "<v5>/n"
   "/c@t"
   "Clear command line	@c /r {<sbold>Esc}	@c (Shift-Esc) @n"         "<v2>@n"
   "Insert file name	@c /r {<sbold>Ctrl-Enter} @c (Ctrl-J) @n" "<v2>@n"
   "Insert file PATH	@c /r {<sbold>Ctrl-F}	@c @n" "<v2>@n"
   "Insert left panel PATH	@c /r {<sbold>Ctrl-[}	@c @n" "<v2>@n"
   "Insert right panel PATH	@c /r {<sbold>Ctrl-]}	@c @n" "<v2>@n"
   "Show history dialog	@c /r {<sbold>Ctrl-K}	@c @n" "<v2>@n"
   "Prev command		@c /r {<sbold>Ctrl-E}	@c @n" "<v2>@n"
   "Next command		@c /r {<sbold>Ctrl-X}	@c @n" "<v2>@n"
   "Execute 		@c /r {<sbold>Enter}	@c @n" "<v2>@n"
   "Execute (without terminal) @c /r {<sbold>Shift-Enter}	@c @n" "<v2>@n"

   "@e/n"
   "<v20>/n"
   ;

const char* helpData_edit =
   "<v10>/n"
   "/c{<shead>Editor help/n}"
   "/c{<shead>Editor Control Keys /n}"
   "<v5>/n"
   "/c@t"
   "Help		@c /r {<sbold>F1}	@n" "<v2>@n"
   "Save		@c /r {<sbold>F2} @c @c  @n""<v2>@n"
   "Save as ...	@c /r {<sbold>Shift-F2} @c @c  @n""<v2>@n"
   "Search		@c /r {<sbold>F7} @n" "<v2>@n"
   "Continue search		@c /r {<sbold>Shift-F7} @n" "<v2>@n"
   "Replace		@c /r {<sbold>Ctrl-F7} @n" "<v2>@n"
   "Charset (change)	@c /r {<sbold>F8} @c (press Shift-F8 to edit Charset list)@n" "<v2>@n"
   "Charset (select)	@c /r {<sbold>Shift-F8} @n" "<v2>@n"
   "Go to line	@c /r {<sbold>Ctrl-G} @c (Alt-F8) @n" "<v2>@n"
   "On//Off Syntax highlighting @c /r {<sbold>Ctrl-H} @c  @n" "<v2>@n"
   "Exit		@c /r {<sbold> F10} @c (Esc, F4)""<v2>@n"
   "<v10>@n"
   "Delete line	@c /r {<sbold> Ctrl-Y}@n""<v2>@n"
   "Cut		@c /r {<sbold> Ctrl-X} @c (Shift-Del)@n""<v2>@n"
   "Copy		@c /r {<sbold> Ctrl-C} @c (Shift-Ins)@n""<v2>@n"
   "Paste		@c /r {<sbold> Ctrl-V} @c (Ctrl-Ins)@n""<v2>@n"
   "<v10>@n"
   "Undo		@c /r {<sbold> Ctrl-Z} @c (Ctrl-BS)@n""<v2>@n"
   "Redo		@c /r {<sbold> Ctrl-Shift-Z} @c @n""<v2>@n"
   "@e/n"
   "<v20>/n"

   "";

const char* helpData_view =
   "<v10>/n"
   "/c{<shead>Viewer Help/n}"
   "/c{<shead>Viewer Control Keys /n}"
   "<v5>/n"
   "/c@t"
   "Help		@c /r {<sbold>F1}	@n" "<v2>@n"
   "Toggle line wrap//unwrap		@c /r {<sbold>F2} @n" "<v2>@n"
   "Toggle hex//text mode		@c /r {<sbold>F4} @n" "<v2>@n"
   "Search		@c /r {<sbold>F7} @n" "<v2>@n"
   "Continue search		@c /r {<sbold>Shift-F7, Space} @n" "<v2>@n"
   "Charset (change)	@c /r {<sbold>F8} @c (press Shift-F8 to edit Charset list) @n" "<v2>@n"
   "Charset (select)	@c /r {<sbold>Shint-F8} @n" "<v2>@n"
//"Go to line  @c /r {<sbold>Ctrl-G} @c (Alt-F8) @n" "<v2>@n"
   "Exit		@c /r {<sbold> F10} @c (Esc, F3)""<v2>@n"
   "<v10>@n"
   "@e/n"
   "<v20>/n"

   "";
