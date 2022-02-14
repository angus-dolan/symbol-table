build: BST classify_line create_func_instance create_var_instance main

BST:
    cl /EHsc /c BST.cpp 
    lib /OUT:BST.lib BST.obj

classify_line:
    cl /EHsc /c classify_line.cpp 
    lib /OUT:classify_line.lib classify_line.obj

create_func_instance:
	cl /EHsc /c create_func_instance.cpp 
    lib /OUT:create_func_instance.lib create_func_instance.obj

create_var_instance:
	cl /EHsc /c create_var_instance.cpp 
    lib /OUT:create_var_instance.lib create_var_instance.obj

main:
    cl /EHsc /c symbol_table.cpp
    link symbol_table.obj BST.lib classify_line.lib create_func_instance.lib create_var_instance.lib

clean:
	del *.lib
	del *.obj
	del *.exe
	del *.asm
   