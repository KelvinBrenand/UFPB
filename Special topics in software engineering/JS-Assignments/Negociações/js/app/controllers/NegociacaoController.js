class NegociacaoController {

    constructor() {

        let $ = document.querySelector.bind(document);

        this._count = 0

        this._inputData = $('#data');
        this._inputQuantidade = $('#quantidade');
        this._inputValor = $('#valor');

        this._listaNegociacao = new ListaNegociacoes();
        this._negociacoesView = new NegociacoesView($('#negociacoes-view'));
        this._negociacoesView.update(this._listaNegociacao);

        this._mensagem = new Mensagem();
        this._mensagemView = new MensagemView($('#mensagem-view'));
        this._mensagemView.update(this._mensagem);
    }

    adiciona(event) {

        event.preventDefault();
        this._listaNegociacao.adiciona(this._criaNegociacao());
        this._negociacoesView.update(this._listaNegociacao);

        this._mensagem.texto = "Negociação adicionada com sucesso!";
        this._mensagemView.update(this._mensagem);

        this._limpaFormulario();
    }

    _criaNegociacao() {
        this._count = this._count+1
        return new Negociacao(
            DateHelper.textoParaData(this._inputData.value),
            this._inputQuantidade.value,
            this._inputValor.value,
            "id"+this._count
        );
    }

    _limpaFormulario() {

        this._inputData.value = '';
        this._inputQuantidade.value = 1;
        this._inputValor.value = 0;
        this._inputData.focus();
    }

    remove(){
        var checkboxes = document.querySelectorAll('input[type=checkbox]:checked')
        for (var i = 0; i < checkboxes.length; i++) {
            this._listaNegociacao.remove(checkboxes[i].id)
        }
        this._negociacoesView.update(this._listaNegociacao);
    }
}