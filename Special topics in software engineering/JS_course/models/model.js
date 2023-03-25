let todos
let count
localStorage.clear();

if (Array.isArray(JSON.parse(localStorage.getItem('todos')))) {
    todos = JSON.parse(localStorage.getItem('todos'))
    count = Number(localStorage.getItem('count'))
} else {
    todos = [{
    title: 'Get groceries',
    dueDate: '2023-03-25',
    id: 'id1'
    },{
    title: 'Wash car',
    dueDate: '2023-03-25',
    id: 'id2'
    },{
    title: 'Make dinner',
    dueDate: '2023-03-25',
    id: 'id3'
    }]
    count = 4
}

function createToDo(title, dueDate, count){
    todos.push({title: title, dueDate: dueDate, id: 'id'+count})
    saveToDos()
}

function removeToDo(idToDelete){
    todos = todos.filter(function (todo){
    return !(todo.id === idToDelete)
    })
    saveToDos()
}

function saveToDos(){
    localStorage.setItem('todos', JSON.stringify(todos))
}

function saveCount(){
    localStorage.setItem('count', JSON.stringify(count))
}