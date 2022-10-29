# Todos App in C++
A console todo app :pushpin: written in C++ with file and DB persistence.
#### Build the project
```bash
g++ -o todo main.cpp --std c++17 
```
#### Following commands are supported, to know more about a command and its options, enter:
```bash
todo help
todo help -c list
todo help --command list
todo help -c create
```
##### Shows help and list of commands
```bash
todo
tood help
```
##### Create a new todo
```bash
todo create --title "Sample todo title."
```
##### List all todos
```bash
todo list
todo list --status complete
tood list --status pending
```
##### Get a single todo
```bash
todo get --index 5
todo get -i 5
```
##### Edit todo title
```bash
todo edit -i 5 -t "new updated todo title."
todo ecit --index 5 --title "new updated todo title."
```
##### Delete todo
```bash
todo delete -i 5
todo delete --index 5
```
##### Mark a todo checked or completed
```bash
todo check -i 5
todo check --index 5
```
##### Mark a todo unchecked or pending
```bash
todo uncheck -i 5
todo uncheck --index 5
```

##### Sample `todo list` output. Don't mind the actual text here :smile:
![Sample todo list output](https://github.com/ShahidYousuf/cpp_todos/blob/master/sample_list_output.png)
