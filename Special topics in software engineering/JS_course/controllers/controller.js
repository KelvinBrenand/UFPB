function addTodo(){
    const title = document.getElementById("todo-title").value
    const dueDate = document.getElementById("date-picker").value
    createToDo(title, dueDate)
    count = count+1
    displayTodos()
}

function deleteTodo(event){
    const idToDelete = event.target.id
    removeToDo(idToDelete)
    displayTodos()
}