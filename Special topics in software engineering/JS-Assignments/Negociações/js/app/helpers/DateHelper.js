class DateHelper {
    constructor() {
        throw new Error('Esta classe não pode ser instânciada.');
    }

    static dataParaTexto(data) {
        return `${data.getDate()}/${data.getMonth()+1}/${data.getFullYear()}`;
    }

    static textoParaData(texto) {
        if(!/^\d{4}-\d{2}-\d{2}$/.test(texto)) {
            throw new Error('O formato do texto deve ser aaaa-mes-dia');
        }
        return new Date(texto.split('-'));
    }
}