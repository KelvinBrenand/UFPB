class Negociacao {
    constructor(data, quantidade, valor, id) {
        this._data = new Date(data.getTime());
        this._quantidade = quantidade;
        this._valor = valor;
        this._id = id;
        Object.freeze(this);
    }

    get data() {
        return new Date(this._data.getTime());
    }

    get quantidade() {
        return this._quantidade;
    }

    get valor() {
        return this._valor;
    }

    get volume() {
        return this._quantidade * this._valor;
    }

    get id(){
        return this._id;
    }
}