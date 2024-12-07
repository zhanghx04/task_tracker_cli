# Task_tracker_CLI
A command line interface task tracker in C++

# How to run
```bash
$ cd task_tracker_cli
$ make
$ ./cli add "New Test"
$ ./cli list
$ ./cli delete 1
$ ./cli mark-in-progress 1
$ ./cli update 1 "Updated the description"
```
> Commands:
>- **add** : Initialize a new task
>- **list** : List all tasks with their details including ID, description, status, creation time, and update time
>- **delete** : Delete a task by its ID
>- **update** : Update a task's description by its ID
>- **mark-in-progress** : Mark a task as "in progress" by its ID
>- **mark-done** : Mark a task as "done" by its ID
>- **list + statu** : List tasks filtered by their status
