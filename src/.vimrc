set tabstop=4
set shiftwidth=4
set softtabstop=4
set noexpandtab		" Real tabs instead of spaces
set nu " Line numbers
set autoindent
syntax on		"Syntax highlighting
set hlsearch	" Last used search pattern highlighted
set ruler		" show the cursor position all the time
set showcmd		" display incomplete commands
set incsearch	" do incremental searching
set mouse=a		" Enable mouse

map <F7> :w <ENTER> :!g++ -Wall -O2 -g -static -o %:r % <ENTER>
map <F5> <F7> <ENTER> :!./%:r <ENTER>
map <F4> <F7> <ENTER> :!./%:r < ~/samples/%:r.in > output.txt <ENTER>
