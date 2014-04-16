kstring
=======

an extension to the C string libraries

kstring layout
--------------
**NB: This is subject to change** <br />
A kstring contains two additional sections not present in a regular C 
string, however the pointer that is returned to the component that is 
a C string so it can be used in regular C string functions. It looks 
somewhat like this.

    purpose | MAGIC    | LENGTH | C STRING |
       type | uint32_t | size_t | char*    |

* MAGIC - a value to be used to check that this is a kstring
* LENGTH - the length of the string
* C STRING - the actual string
