let shoppingList = [{
	title:'Notebook', id:'id1'
	},{
		title:'Jello', id:'id2'
	},{
		title:'Spinach', id:'id3'
	},{
		title:'Rice', id:'id4'
	},{
		title:'Birthday Cake', id:'id5'
	},{
		title:'Candles', id:'id6'
	}]

let count = 7

let input = document.getElementById("userinput");
let button = document.getElementById("enter");

function inputLength(input) {
	return input.length;
}

function createListElement() {
	let ul = document.querySelector("ul")
	ul.innerHTML=""

	shoppingList.forEach(function(element){
		var li = document.createElement("li");
		li.style = "padding-bottom:10px;"

		var div1 = document.createElement("div")
		div1.style = "display: flex;"

		var div2 = document.createElement("div")
		div2.style = "inline-size:150px; overflow-wrap: break-word; hyphens: manual;"
		div2.className = "settingOne"
		div2.id = element.id
		div2.onclick = changeClass
		div2.innerText = element.title

		var div3 = document.createElement("div")
		div3.style = "margin-left:10px;"

		const deleteButton = document.createElement('button')
		deleteButton.innerText ='Delete'
		deleteButton.style = 'margin-left: 10px;'
		deleteButton.onclick = removeItem
		deleteButton.id = element.id
		div3.appendChild(deleteButton)

		div1.append(div2, div3)
		li.appendChild(div1)
		ul.appendChild(li);
	})
}

function addListAfterClick() {
	newItem(input.value)
	count = count+1
	createListElement();
}

function addListAfterKeypress(event) {
	if (event.keyCode === 13) {
		newItem(input.value)
		count = count+1
		createListElement();
	}
}

button.addEventListener("click", addListAfterClick);

input.addEventListener("keypress", addListAfterKeypress);

function newItem(input){
	if (inputLength(input) > 0) {
		shoppingList.push({title: input, id: 'id'+count})
	}
}

function removeItem(event){
	const idToDelete = event.target.id
	shoppingList = shoppingList.filter(function (item){
        if (item.id === idToDelete) {
          return false
        } else{
          return true
        }
      })
	createListElement()
  }

function changeClass() {
	if (document.getElementById(this.id).className == "settingOne") {
		document.getElementById(this.id).className = "done";
	} else {
		document.getElementById(this.id).className = "settingOne";
	}
}