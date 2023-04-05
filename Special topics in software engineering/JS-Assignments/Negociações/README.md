# alura-javascript-avancado
Curso de JavaScript Avançado do [Alura][alura] - Módulos [I][curso1], [II][curso2] e [III][curso3].

Este repositório contém a minha visão sobre os cursos, as lições aprendidas e o projeto desenvolvido durante os cursos.

## O curso

Neste curso o instrutor [Flavio Henrique de Souza Almeida][flavio] nos ensina como desenvolver utilizando `Orientação a Objetos` com `JavaScript` e aplicar conceitos do padrão `MVC` durante o desenvolvimento de um projeto. Ele nos apresenta diversas novidades incluídas no `JavaScript` a partir do `ECMAScript 2015`, além de algumas dicas e macetes sobre `JavaScript` que podem nos ajudar no dia-a-dia do desenvolvimento.

O projeto resultante desse curso está armazenado nesse repositório e pode ser visualizado [neste link][repo]. Ele está hospedado aqui no GitHub utilizando o [GitHub Pages][github-pages].

## Lições aprendidas

Na minha visão as principais lições aprendidas estão listadas abaixo.

#### 0. MVC no Front-End
#### 1. Definição de classes
#### 2. Variáveis com escopo de bloco
#### 3. Objetos imutáveis
#### 4. this() e bind()
#### 5. Evitando percorrer o DOM
#### 6. new Date() e string
#### 7. Array
#### 8. Spread operator
#### 9. Arrow functions
#### 10. Métodos estáticos
#### 11. Template Strings e interpolação
#### 12. Herança

---

#### 0. MVC no Front-End

>MVC é nada mais que um padrão de arquitetura de software, separando sua aplicação em 3 camadas.
>A camada de interação do usuário(view), a camada de manipulação dos dados(model) e a camada de controle(controller).
>
> -- <cite>[Allan Ramos][citacao]</cite>

Minha maior experiência até o momento havia sido com `Java` no Back-End das aplicações e o uso do `MVC` é comum há muito tempo. Quando comecei a estudar sobre o uso desse padrão no Front-End me empolguei bastante, pois isso gera uma boa organização do código, dando maior legibilidade e tornando a manutenção do código muito mais fácil.
Aplicando esse padrão no desenvolvimento, cada camada fica com uma responsabilidade bem definida. Juntando com a `Orientação a Objetos` fica muito mais fácil saber onde colocar um código para incrementar uma funcionalidade ou até mesmo criar uma nova.

---

#### 1. Definição de classes

JavaScript é uma linguagem que permite o desenvolvimento seguindo 3 paradigmas de programação: Estruturada, Funcional e Orientada a Objetos.

Porém o uso de Orientação a Objetos na linguagem era possível através do uso de `prototype` e essa escrita era considerada um pouco verbosa e complexa por muitas pessoas. Com isso uma das novidades a versão 6 do ECMAScript, o `ES2015`, foi uma nova sintaxe para definição de classes.

O código escrito com `prototype` abaixo:

```javascript
function Pessoa(nome, sobrenome) {
    this.nome = nome;
    this.sobrenome = sobrenome;
}
Pessoa.prototype.obterNomeCompleto = function() {
    return this.nome + ' ' + this.sobrenome;
};
```

Pode ser escrito com essa nova sintaxe a partir do `ES2015`:

```javascript
class Pessoa {
    constructor(nome, sobrenome) {
        this.nome = nome;
        this.sobrenome = sobrenome;
    }
    obterNomeCompleto() {
        return `${this.nome} ${this.sobrenome}`;
    }
}
```

A definição de uma classe com um construtor, propriedades definidas com getters e métodos utilizando a sintaxe do `ES2015` fica da seguinte maneira:

```javascript
//Definição da classe
class Pessoa {
    
    //Construtor da classe, onde é possível receber parâmetros
    constructor(nome, sobrenome) {
        this._nome = nome;
        this._sobrenome = sobrenome;
    }

    //Definição de um getter para a classe
    get nome() {
        return this._nome;
    }

    //Método definido na classe 
    obterNomeCompleto() {
        return `${this.nome} ${this.sobrenome}`;
    }
}
```

---

#### 2. Variáveis com escopo de bloco

Outra novidade do ES2015 foi a inclusão da keyword `let` para definir variáveis com escopo de bloco e validação para que a mesma variável não seja criada mais de uma vez. Antes disso a declaração de variáveis utilizando `var` tinha escopo global ou de função. Exemplo:

```javascript
function testeVar() {
    for(var i = 1; i<= 10; i++) {
        var nome = 'Jefferson';
        //mais código...
    }

    console.log(i); // "11" é exibido no console
    console.log(nome); // "Jefferson" é exibido no console
}

function testeLet() {
    for(let i = 1; i<= 10; i++) {
        let nome = 'Jefferson';
        //mais código...
    }

    console.log(i); //Aqui já é apresentado um erro dizendo que "i" não foi definido.
    console.log(nome);
}
```

---

#### 3. Objetos imutáveis

O JavaScript ainda não permite que sejam criadas propriedades/atributos privados, então por convenção utiliza-se o prefixo `_` para indicar propriedades/atributos que são privados. Além disso, uma técnica utilizada para que essas propriedades/atributos passem a ser `imutáveis` é a utilização do método `Object.freeze`. Um exemplo seria:

```javascript
class Pessoa {
    constructor(nome) {
        this._nome = nome;
        // A partir da execução da linha abaixo as propriedades desse objeto não podem sofrer alterações
        Object.freeze(this);
    }

    get nome() {
        return this._nome;
    }

}
```

---

#### 4. this() e bind()

Em JavaScript é possível atribuir uma função à uma variável, e posteriormente executarmos a função por meio dessa variável. Por exemplo, poderiamos atribuir a função `document.querySelector()` para uma variável chamada `$`, dessa forma estariamos imitando o seletor do jQuery e poderiamos selecionar os elementos com a sintaxe `$()`. Como no código abaixo:

```javascript
var $ = document.querySelector;

let formulario = $('.form');
```

Porém o código acima não funciona! Internamente a função `document.querySelector()` faz referência ao `this`, e quando associamos essa função à variável `$` ela perde o contexto e quando é executada a chamada ao `this` gera um erro. Neste caso devemos utilizar a função `bind()` para associar o contexto `document` a variável `$`.

```javascript
var $ = document.querySelector.bind(document);

let formulario = $('.form');
```

Dessa forma quando a função for executada através do `$('.form')` o `this` faz referência a `document`, que foi o contexto associado atravéz do `bind()`.

---

#### 5. Evitando percorrer o DOM

Quando temos uma função/método que irá selecionar um elemento no DOM como é feito no `incrementa()` abaixo:

```javascript
class ContadorController {
    constructor() {
        this._contador = 0;
        alert(this._contador);
    }

    get contador() {
        return this._contador;
    }

    incrementa() {
        this._contador++;
        document.querySelector('#p1').textContent = this._contador;
    }
}
```

Toda vez que `incrementa()` for executado, a árvore de elementos do DOM será percorrida para achar o elemento com o id `#p1`. Em uma aplicação pequena isso não irá gerar problemas, mas conforme a aplicação crescer isso poderá gerar problemas de performance pois percorrer o DOM é uma tarefa custosa para o browser. Uma boa prática que deve ser feita é salvar uma referência desse elemento em uma variável para que não seja necessário percorrer o DOM toda vez que precisarmos do elemento. O código refatorado ficaria da seguinte forma:

```javascript
class ContadorController {
    constructor() {
        this._contador = 0;
        this._elemento = document.querySelector('#p1'); // busca uma única vez
        alert(this._contador);
    }

    get contador() {
        return this._contador;
    }

    incrementa() {
        this._contador++;
        this._elemento.textContent = this._contador; // não precisa buscar o elemento, já temos uma referência para ele
    }
}
```

---

#### 6. new Date(), string

Temos várias formas de construir um objeto do tipo `Date`, alguns exemplos são:

```javascript
console.log(new Date('2016/05/17')); // string no formato AAAA/MM/DD
console.log(new Date(['2016', '05', '17'])); // array de string com os elementos ano, mês e dia
console.log(new Date([2016, 05, 17])); // array de number com os elementos ano, mês e dia
console.log(new Date(2016, 4, 17)); // passando separadamente o ano, mês (iniciando com janeiro em 0) e o dia
```

Mas em portugues geralmente temos a data apresentada no formato dia, mês e ano. Então quase sempre teremos que fazer conversões no dado antes de instânciar um objeto `Date`. Para exemplificar, vamos considerar a data `17-05-2016` no código abaixo. Sendo uma string, podemos chamar a função `split()` passando qual será o delimitador para dividir a string e criar um array. Com um Array podemos utilizar as funções `reverse()` e `join()` que inverte a ordem de todos os elementos do array e concatena todos os elementos do array com o delimitador informado gerando uma string.

```javascript
let dataString3 = '17-05-2016';

let data1 = new Date(dataString3.split('-').reverse()); // deixa o parâmetro no formato ["2016", "05", "17"]
let data2 = new Date(dataString3.split('-').reverse().join('/')); // deixa o parâmetro no formato '2016/05/17'
```

#### 7. Array

Arrays em javascript também possuem uma função muito prática chamada `map()`. Essa função itera sobre todos os elementos do array e aplica a função recebida como parâmetro em todos esses elementos. No exemplo abaixo temos um array de números, nele aplicamos uma função que dobra o valor de todos os números que forem impar.

```javascript
let numeros = [3,2,11,20,8,7];

let novosNumeros = numeros.map(numero => numero % 2 ? numero * 2 : numero);

console.log(novosNumeros); // [6, 2, 22, 20, 8, 14]
```

Outra função que pode ser muito útil é a `reduce()`. A função `reduce()` recebe como parâmetro uma função com dois parâmetros, o primeiro é um acumulador e o segundo é o elemento da iteração atual. O acumulador será o retorno da função `reduce()`, além disso podemos também passar como segundo parâmetro um valor inicial para esse acumulador. O código de exemplo retorna a somatória de todos os elementos do array.

```javascript
let numeros = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

let somatoria = numeros.reduce((total, num) => {
    return total + num; //somamos o acumulador 'total' com o elemento atual 'num'
, 0); // inicializamos o acumulador 'total' com o valor '0'

console.log(somatoria); // exibe 55
```

---

#### 8. Spread operator

O `Spread operator` é outra novidade na sintaxe do `ES2015`. Ele é usado para separar os elementos de um array, por exemplo, a função `Array.push()` pode receber 1 ou mais elementos como parâmetro. Utilizando o `Spread operator` é possível passar um outro array que todos os elementos são desmembrados e passados separadamente como parâmetros. Utilizando `ES5` poderia ser feito da seguinte forma:

```javascript
var lista1 = ['banana', 'laranja', 'mamão'];
var lista2 = ['caju', 'tangerina', 'abacaxi'];

for (i = 0; i < lista2.length; i++) { 
    lista1.push(lista2[i]);
}
```

Já com o `Spread operator` do `ES2015`:

```javascript
let lista1 = ['banana', 'laranja', 'mamão'];
let lista2 = ['caju', 'tangerina', 'abacaxi'];

lista1.push(...lista2);
```

---

#### 9. Arrow functions

`Arrow function` é uma nova sintaxe para simplificar a escrita de código, deixando-o menos verboso. Abaixo temos um exemplo utilizando a função `Array.filter()`, ela recebe uma função como parâmetro e essa função recebe cada um dos elementos do array e deve retornar `true` para que o elemento faça parte do array resultante ou `false` para excluir o elemento do array resultante.

```javascript
let numeros = [1,2,3,4,5,6,7,8,9,10];
let pares = numeros.filter(function(num) {
    return num % 2 == 0;
});
```

Neste exemplo estamos filtrando um array de numeros para criar um novo array somente com os números que forem pares. Aplicando o `Arrow function` ficaria da seguinte forma:

```javascript
let numeros = [1,2,3,4,5,6,7,8,9,10];
let pares = numeros.filter((num) =>  { return num % 2 == 0; });
```

A palavra `function` é descartada e somente seus parâmetros são mantidos, em seguida é adicionado uma 'flecha' `=>` e depois vem o corpo normal da função.

Porém nesse caso em específico, que temos somente um parâmetro e que o retorno da função é um único comando (`return num % 2 == 0;`), podemos deixar o código mais enxuto ainda eliminando os parênteses do parâmetro, as chaves que delimitam o corpo da função e a palavra `return`:

```javascript
let numeros = [1,2,3,4,5,6,7,8,9,10];
let pares = numeros.filter(num => num % 2 == 0);
```

---

#### 10. Métodos estáticos

Os métodos definidos nas classes são métodos de instância, ou seja, podem ser executados em um objeto daquela classe. Porém é possível também definir métodos que não necessitam de uma instância da classe para que sejam executados, basta definir o método como estático. O código abaixo mostra um exemplo de como definir e executar um método estático.

```javascript
class DateHelper {
    constructor() {
        throw new Error('Esta classe não pode ser instânciada.');
    }

    //Método estático
    static dataParaTexto(data) {
        return `${data.getDate()}/${data.getMonth()+1}/${data.getFullYear()}`;
    }

    //Método estático
    static textoParaData(texto) {
        if(!/^\d{4}-\d{2}-\d{2}$/.test(texto)) {
            throw new Error('O formato do texto deve ser aaaa-mes-dia');
        }
        return new Date(texto.split('-'));
    }
}

//Uso
console.log(DateHelper.dataParaTexto(new Date()));
```

---

#### 11. Template Strings e interpolação

Utilizando `ES2015` é possível utilizar a sintaxe de `Template String`. Como podemos ver no código abaixo, quando precisamos que uma string seja interpolada com variáveis não é mais necessário fazer a concatenação utilizando o sinal de `+`, basta utilizar o `Template String` que o valor da variável é colocado na string gerada.

```javascript
let nome = 'Jefferson';
let sobrenome = 'Martins de Andrade';

let frase = `${nome} ${sobrenome} é um desenvolvedor!`; //Jefferson Martins de Andrade é um desenvolvedor!
```

Um ponto importante em relação ao `Template String` é que a string deve ser envolvida com crase ao invés de aspas duplas ou simples.

---

#### 12. Herança

A utilização do `ES2015` também permite que seja utilizada herança entre as classes criadas com o uso da keyword `extends`. Porém ainda não é possível a criação de classes ou métodos abstratos. Seu uso fica conforme o código abaixo.

```js
class View { }

class MensagemView extends View { }
```


[alura]: https://www.alura.com.br
[citacao]: https://tableless.com.br/mvc-afinal-e-o-que/
[curso1]: https://www.alura.com.br/curso-online-javascript-es6-orientacao-a-objetos-parte-1
[curso2]: https://www.alura.com.br/curso-online-javascript-es6-orientacao-a-objetos-parte-2
[curso3]: https://www.alura.com.br/curso-online-javascript-es6-orientacao-a-objetos-parte-3
[flavio]: https://cursos.alura.com.br/user/flavio-almeida
[github-pages]: https://pages.github.com/
[repo]: https://jeffersondev.github.io/alura-javascript-avancado/