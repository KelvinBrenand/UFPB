function displayTodos(){
    document.getElementById("todo-list").innerHTML=""

    todos.forEach(function(todo){
    const element = document.createElement('div')
    element.innerText = todo.title + ' ' + todo.dueDate
    document.getElementById("todo-list").appendChild(element)

    const deleteButton = document.createElement('button')
    deleteButton.innerText ='Delete'
    deleteButton.style = 'margin-left: 12px'
    deleteButton.onclick = deleteTodo
    deleteButton.id = todo.id
    element.appendChild(deleteButton)
    })
}