package syntax;

import exceptions.SyntaxException;
import lexical.Scanner;
import lexical.Token;
import utils.TokenType;

public class Parser {
	private Scanner scanner;
	private Scanner testScanner;
	private Token token;
	private Token testToken;

	public Parser(Scanner scanner, Scanner testScanner) {
		this.scanner = scanner;
		this.testScanner = testScanner;
	}

	public void programa(){
		verifyType(TokenType.COLON);
		verifyContent("DECLARACOES", null);
		listaDeclaracoes();

		verifyType(TokenType.COLON);
		verifyContent("ALGORITMO", null);
		listaComandos();
	}
	private void testTokenChecker(){
		this.testScanner.setRow(this.scanner.getRow());
		this.testScanner.setColumn(this.scanner.getColumn());
		this.testToken = this.testScanner.nextToken();
	}
	private void listaDeclaracoes(){
		testTokenChecker();
		if(!this.testToken.getContent().equals("INTEIRO") && !this.testToken.getContent().equals("REAL")){
			//vazio
		}else{
			declaracao();
			listaDeclaracoes();
		}
	}
	private void declaracao(){
		verifyContent("INTEIRO", "REAL");
		verifyType(TokenType.COLON);
		varLista();
		verifyType(TokenType.SEMICOLON);
	}
	private void varLista(){
		verifyType(TokenType.IDENTYFIER);
		testTokenChecker();
		if(this.testToken.getContent().equals(",")){
			verifyType(TokenType.COMMA);
			varLista();
		}
	}
	private void listaComandos() {
		comando();
		listaComandos2();
	}
	private void comando() {
		testTokenChecker();
		if(this.testToken.getContent().equals("ASSIGN")){
			comandoAtribuicao();
		}else if(this.testToken.getContent().equals("INPUT")){
			comandoEntrada();
		}else if(this.testToken.getContent().equals("PRINT")){
			comandoSaida();
		}else if(this.testToken.getContent().equals("IF")){
			comandoCondicao();
		}else if(this.testToken.getContent().equals("WHILE")){
			comandoRepeticao();
		}
	}
	private void listaComandos2() {
		testTokenChecker();
		if(!this.testToken.getContent().equals("ASSIGN") && 
			!this.testToken.getContent().equals("INPUT") && 
			!this.testToken.getContent().equals("PRINT") && 
			!this.testToken.getContent().equals("IF") && 
			!this.testToken.getContent().equals("WHILE")){
			//vazio
		}else{
			listaComandos();
		}
	}
	private void comandoAtribuicao(){
		verifyContent("ASSIGN", null);
		expressaoAritmetica();
		verifyContent("TO", null);
		verifyType(TokenType.IDENTYFIER);
		verifyType(TokenType.SEMICOLON);
	}
	private void comandoEntrada(){
		verifyContent("INPUT", null);
		verifyType(TokenType.IDENTYFIER);
		verifyType(TokenType.SEMICOLON);
	}
	private void comandoSaida(){
		verifyContent("PRINT", null);
		verifyType(TokenType.LEFT_PARENTHESIS);
		testTokenChecker();
		if(testToken.getType() == TokenType.IDENTYFIER){
			verifyType(TokenType.IDENTYFIER);
		}else if(testToken.getType() == TokenType.CADEIA){
			verifyType(TokenType.CADEIA);
		}
		verifyType(TokenType.RIGHT_PARENTHESIS);
		verifyType(TokenType.SEMICOLON);
	}
	private void comandoCondicao(){
		verifyContent("IF", null);
		expressaoRelacional();
		verifyContent("THEN", null);
		listaComandos();
		comandoCondicao2();
	}
	private void comandoCondicao2(){
		testTokenChecker();
		if(!this.testToken.getContent().equals("ELSE")){
			//vazio
		}else{
			verifyContent("ELSE", null);
			listaComandos();
		}
	}
	private void comandoRepeticao(){
		verifyContent("WHILE", null);
		expressaoRelacional();
		listaComandos();
	}
	private void expressaoRelacional(){
		termoRelacional();
		expressaoRelacional2();
	}
	private void expressaoRelacional2() {
		testTokenChecker();
		if(!this.testToken.getContent().equals("AND") && !this.testToken.getContent().equals("OR")){
			//vazio
		}else{
			verifyContent("AND", "OR");
			expressaoRelacional();
		}
	}
	private void termoRelacional(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.LEFT_PARENTHESIS){
			verifyType(TokenType.LEFT_PARENTHESIS);
			expressaoRelacional();
			verifyType(TokenType.RIGHT_PARENTHESIS);
		}else{
			expressaoAritmetica();
			verifyType(TokenType.REL_OP);
			expressaoAritmetica();
		}
	}
	private void expressaoAritmetica(){
		termoAritmetico();
		expressaoAritmetica2();
	}
	private void expressaoAritmetica2(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.SUM || this.testToken.getType() == TokenType.SUBTRACTION){
			expressaoAritmetica3();
			expressaoAritmetica2();
		}else{
			//vazio
		}
	}
	private void expressaoAritmetica3(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.SUM){
			verifyType(TokenType.SUM);
			termoAritmetico();
		}else if(this.testToken.getType() == TokenType.SUBTRACTION){
			verifyType(TokenType.SUBTRACTION);
			termoAritmetico();
		}
	}
	private void termoAritmetico(){
		fatorAritmetico();
		termoAritmetico2();
	}
	private void termoAritmetico2(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.MULTIPLICATION || this.testToken.getType() == TokenType.DIVISION){
			termoAritmetico3();
			termoAritmetico2();
		}else{
			//vazio
		}
	}
	private void termoAritmetico3(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.MULTIPLICATION){
			verifyType(TokenType.MULTIPLICATION);
			fatorAritmetico();
		}else if(this.testToken.getType() == TokenType.DIVISION){
			verifyType(TokenType.DIVISION);
			fatorAritmetico();
		}
	}
	private void fatorAritmetico(){
		testTokenChecker();
		if(this.testToken.getType() == TokenType.LEFT_PARENTHESIS){
			verifyType(TokenType.LEFT_PARENTHESIS);
			expressaoAritmetica();
			verifyType(TokenType.RIGHT_PARENTHESIS);
		}else{
			this.token = this.scanner.nextToken();
			if (this.token.getType() != TokenType.NUMBER && this.token.getType() != TokenType.IDENTYFIER) {
				throw new SyntaxException("INTEIRO or REAL or VARIAVEL expected, found " + token.getContent());
			}
		}
	}

	private void verifyType(TokenType type){
		this.token = this.scanner.nextToken();
		if (this.token.getType() != type) {
			throw new SyntaxException(type +" expected, found " + token.getContent());
		}
	}
	private void verifyContent(String str1, String str2){
		this.token = this.scanner.nextToken();
		if(str2 == null){
			if (!this.token.getContent().equals(str1)) {
				throw new SyntaxException("'"+str1+"'"+" keyword expected, found " + token.getContent());
			}
		}else{
			if (!this.token.getContent().equals(str1) && !this.token.getContent().equals(str2)) {
				throw new SyntaxException("'"+str1+"'"+" or "+"'"+str2+"'"+" keyword expected, found " + token.getContent());
			}
		}
	}
}