Introduction

Address Book:
It's a command line application developed by C programming language. 
You can manage address book by adding, searching and removing address entries, the "display" and "save" operation is also available and it is convenient for you to create a new address book file or reload an existed address book file on file system.

Development environment

Linux version 2.6.35-32-generic (buildd@vernadsky) 
gcc version 4.4.5 (Ubuntu/Linaro 4.4.4-14ubuntu5)
 
Features

Detail information of every address entry:
- name of the person
- mobile number of the person
- home address of the person

start interactive command line application:

sh>./a.out
addressbook> _
create a new address book file:
sh>./a.out -f:/xxx/xxx/ab -new
First create Ok!
The file path and name is: xxx/xxx/ab
addressbook>_

reload an existed address book file:

There are two ways to reload an existed file, for example:
if file: ab is existed:

sh>./a.out -f:/xxx/xxx/ab
Open file: ab successfully!
addressbook>_

or

addressbook>reload
file path: /xxx/xxx/ab
Now reloading...
Successfully reloaded!
addressbook>_

add a new address entry:

addressbook>add
name: xiaoming
mobile: 18888888888
address: xiaoming jia
Address entry added.
addressbook>add
name: xiaofang
mobile: 13333333333
address: xiaofang jia
Address entry added.
addressbook>_

exact search:

addressbook>search
by (name|mobile|address):name
name: xiaoming
1 search result:
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
---------------------------
addressbook> _

fuzzy search:

addressbook>search
by (name|mobile|address):name
name: xiao.*
2 search results:
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
---------------------------
name: xiaofang
mobile: 13333333333
address: xiaofang jia
---------------------------
addressbook>_

display all the address entries:

addressbook>display
record 1
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
record 2
---------------------------
name: xiaofang
mobile: 13333333333
address: xiaofang jia
addressbook>_

remove one or more address entries:

addressbook>delete
by (name|mobile|address):address
address: xiao.*
2 address entries deleted
addressbook>_

save to an address book file:

if file path hasn't been assigned:

addressbook>save
file path: /xxx/xxx/ab
Now saving...
Successfully saved!
addressbook>_

if file path has been already assigned:

addressbook>save
Now saving...
Successfully saved!
addressbook>_

get help:

addressbook>!help
---------Help information--------
The address commands are defined internally.
xxxxxxxxx
xxxxxxxxx
addressbook>_

quit from the application:

addressbook>!quit
sh>_
Introduction

Address Book:
It¡¯s a command line application developed by C programming language. 
You can manage address book by adding, searching and removing address entries, the ¡°display¡± and ¡°save¡± operation is also available and it is convenient for you to create a new address book file or reload an existed address book file on file system.

Development environment

Linux version 2.6.35-32-generic (buildd@vernadsky) 
gcc version 4.4.5 (Ubuntu/Linaro 4.4.4-14ubuntu5)
 
Features

Detail information of every address entry:
- name of the person
- mobile number of the person
- home address of the person

start interactive command line application:

sh>./a.out
addressbook> _
create a new address book file:
sh>./a.out ¨Cf:/xxx/xxx/ab ¨Cnew
First create Ok!
The file path and name is: xxx/xxx/ab
addressbook>_

reload an existed address book file:

There are two ways to reload an existed file, for example:
if file: ab is existed:
sh>./a.out ¨Cf:/xxx/xxx/ab
Open file: ab successfully!
addressbook>_

or

addressbook>reload
file path: /xxx/xxx/ab
Now reloading...
Successfully reloaded!
addressbook>_

add a new address entry:

addressbook>add
name: xiaoming
mobile: 18888888888
address: xiaoming jia
Address entry added.
addressbook>add
name: xiaofang
mobile: 13333333333
address: xiaofang jia
Address entry added.
addressbook>_

exact search:

addressbook>search
by (name|mobile|address):name
name: xiaoming
1 search result:
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
---------------------------
addressbook> _

fuzzy search:

addressbook>search
by (name|mobile|address):name
name: xiao.*
2 search results:
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
---------------------------
name: xiaofang
mobile: 13333333333
address: xiaofang jia
---------------------------
addressbook>_

display all the address entries:

addressbook>display
record 1
---------------------------
name: xiaoming
mobile: 18888888888
address: xiaoming jia
record 2
---------------------------
name: xiaofang
mobile: 13333333333
address: xiaofang jia
addressbook>_

remove one or more address entries:

addressbook>delete
by (name|mobile|address):address
address: xiao.*
2 address entries deleted
addressbook>_

save to an address book file:

if file path hasn¡¯t been assigned:

addressbook>save
file path: /xxx/xxx/ab
Now saving...
Successfully saved!
addressbook>_

if file path has been already assigned:

addressbook>save
Now saving...
Successfully saved!
addressbook>_

get help:

addressbook>!help
---------Help information--------
The address commands are defined internally.
xxxxxxxxx
xxxxxxxxx
addressbook>_

quit from the application:

addressbook>!quit
sh>_
