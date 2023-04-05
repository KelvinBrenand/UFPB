class ListaNegociacoes {
    constructor() {
        this._listaNegociacoes = [];
    }

    adiciona(negociacao) {
        this._listaNegociacoes.push(negociacao);
    }

    remove(id){
        this._listaNegociacoes = this._listaNegociacoes.filter(negociacao => negociacao.id !== id);
    }

    get negociacoes() {
        return [].concat(this._listaNegociacoes);
    }
}