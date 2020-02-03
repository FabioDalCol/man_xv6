# Xv6 man implementation  
A simplified version of **man** for xv6.

## Building directory structure  
First of all, **init** has been edited to execute at startup a process called **manbuild** which check if **man **working directories are present and eventually generates them.  
*/manpages* directory contains 8 subdirectories (man1,man2,man3,man4,man5,man6,man7,man8), one for each man section.

## man

Like in the orginal version manpages are organized in 8 section as follows:

| Section | Type |
| ------ | ------ |
| 1 | Executable or shell programs |
| 2 | System calls |
| 3 | Library calls |
| 4 | Special files |
| 5 | File formats |
| 6 | Games |
| 7 | Miscellaneous |
| 8 | System administration commands |


### Options  
**man [command name]**   
Passing the man command followed by a command name without any option will output the first matching man page.

**man [section number] [command name]**  
Passing the man command followed by section number followed by a command name will outuput the corrisponding man page from the section chosen.

**man -f [command name]**  
Output all the corrisponding man pages followed by the section number in which are contained.

**man -w [command name]**  
Returns the locations in which the man pages of a given command is present.

## manadd

To simplfy the process of adding a new man page, a specific tool has been developed: **manadd**.

Each man page is divided in 5 paragrafs: **NAME**, **SYNOPSIS**, **DESCRIPTION**, **OPTIONS**, **AUTHOR**.

The syntax to add a new man page is the following:

**manadd [section number] [command name]**

It is then possible to write, using the console, each paragraf of the man page. When drafting of a paragraf has ended is sufficient to send the char '&' on a new line to skip to the next paragraf. 
At the end the new page will be stored in the corrisponding man section.

## Testing

Man page for **man** has been added to the main folder of this lab. A small portion of code has been added to **manbuild** to move this man page to the correct directory when xv6 boots for the first time.

In the shell type:

```bash
man man
```

to display the manuale page of **man**.  
To test other parameters of **man** it is convenient to add new man pages through **manadd**.

## Extra

Function ***strcat()*** (used to attach two strings) has been added to **ulib** and decladered in **user.h**.  
Credits for the code of this function goes to: 

Aurelien Vallee
https://github.com/NewbiZ/xv6/blob/master/distrib/ulibc/src/string/strcat.c
