package lexical;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import utils.TokenType;

public class Scanner {
	int state, dataLength, row=0, column=-1;
	List<String> KEYWORDS = Arrays.asList("int", "float", "print", "if", "else");
	String[] arr = null;

	public Scanner(String filename) {
		try {
			String contentBuffer = new String(Files.readAllBytes(Paths.get(filename)), StandardCharsets.UTF_8);
			this.arr = contentBuffer.toString().split("\n");
			dataLength = getDataLength();
		} catch (IOException e) {e.printStackTrace();}
	}
	public Token nextToken() {
		this.state = 0;
		String content = "";
		char currentChar;
		while(true){
			currentChar = this.nextchar();
			switch (state) {
			case 0: //Base Case
				if (this.isLetter(currentChar)) {
					content += currentChar;
					state = 1;
					try {
						this.arr[this.row].charAt(this.column+1);
					} catch (Exception e) {
						return new Token(TokenType.IDENTYFIER, content);
					}
				} else if (isSpace(currentChar)) {
					state = 0;
				} else if (isDigit(currentChar)) {
					content += currentChar;
					state = 2;
					try {
						this.arr[this.row].charAt(this.column+1);
					} catch (Exception e) {
						return new Token(TokenType.NUMBER, content);
					}
				}else if(currentChar == '.'){
					content += "0.";
					state = 2;
				} else if(isOperator(currentChar)){
					content += currentChar;
					state = 3;
					try {
						this.arr[this.row].charAt(this.column+1);
					} catch (Exception e) {
						return new Token(TokenType.REL_OP, content);
					}
				} else if(isAssign(currentChar)){
					content += currentChar;
					return new Token(TokenType.ASSIGNMENT, content);
				} else if(isCommentary(currentChar)){
					content = "";
					this.row++;
					this.column=-1;
				} else if(isSum(currentChar)){
					content += currentChar;
					return new Token(TokenType.SUM, content);
				} else if(isSubtraction(currentChar)){
					content += currentChar;
					return new Token(TokenType.SUBTRACTION, content);
				} else if(isMultiplication(currentChar)){
					content += currentChar;
					return new Token(TokenType.MULTIPLICATION, content);
				} else if(isDivision(currentChar)){
					content += currentChar;
					return new Token(TokenType.DIVISION, content);
				} else if(isLeftParenthesis(currentChar)){
					content += currentChar;
					return new Token(TokenType.LEFT_PARENTHESIS, content);
				} else if(isRightParenthesis(currentChar)){
					content += currentChar;
					return new Token(TokenType.RIGHT_PARENTHESIS, content);
				} else {
					throw new RuntimeException("Unrecognized Symbol at row " + (row+1) + " column " + column);
				}
				break;
			case 1: //Identificator Case
				if (this.isLetter(currentChar) || this.isDigit(currentChar) || this.isUnderscore(currentChar)) {
					content += currentChar;
					state = 1;
					try {
						this.arr[this.row].charAt(this.column+1);
					} catch (Exception e) {
						return isReservedWord(content) ? new Token(TokenType.KEYWORD, content) : new Token(TokenType.IDENTYFIER, content);
					}
				} else if(isSpace(currentChar)){
					this.back();
					return isReservedWord(content) ? new Token(TokenType.KEYWORD, content) : new Token(TokenType.IDENTYFIER, content);
				}else if(isRightParenthesis(currentChar)){
					this.back();
					return isReservedWord(content) ? new Token(TokenType.KEYWORD, content) : new Token(TokenType.IDENTYFIER, content);
				}else{
					throw new RuntimeException("Malformed identificator at row " + (row+1) + " column " + column);
				}
				break;
			case 2: //Digit Case
				boolean endOfNumber = false;
				try {
					this.arr[this.row].charAt(this.column+1);
				} catch (Exception e) {
					endOfNumber = true;
				}
				if(isDigit(currentChar)) {
					content += currentChar;
					state = 2;
					if(endOfNumber){ return new Token(TokenType.NUMBER, content);}
				}else if(currentChar == '.'){
					if(content.contains(".")){
						throw new RuntimeException("Malformed Number at row " + (row+1) + " column " + column);
					} else{
						content += currentChar;
						state = 2;
						if(endOfNumber){ throw new RuntimeException("Malformed Number at row " + (row+1) + " column " + column);}
					}
				} else if(isLetter(currentChar)) {
					throw new RuntimeException("Malformed Number at row " + (row+1) + " column " + column);
				} else {
					this.back();
					if(content.endsWith(".")){
						throw new RuntimeException("Malformed Number at row " + (row+1) + " column " + column);
					}else{
						return new Token(TokenType.NUMBER, content);
					}
				}
				break;
			case 3: //Operator Case
				try {
					this.arr[this.row].charAt(this.column+1);
				} catch (Exception e) {
					return new Token(TokenType.REL_OP, content);
				}
				if (this.isAssign(currentChar)){
					if(content.contains("=")){
						throw new RuntimeException("Malformed relational operator at row " + (row+1) + " column " + column);
					}
					content += currentChar;
					state = 3;
				}else{
					if (isSpace(currentChar)) {
						this.back();
						return new Token(TokenType.REL_OP, content);
					} else {
						throw new RuntimeException("Malformed relational operator at row " + (row+1) + " column " + column);
					}
				}
			}
		}
	}
	private char nextchar() {
		try {
			this.column++;
			return this.arr[this.row].charAt(this.column);
		} catch (Exception e) {
			this.column=0;
			this.row++;
			if(isEOF()){
				System.exit(0);
				return 'c'; //Java me obriga a retornar um char, mesmo que essa instrução nunca seja alcançada.
			}else{
				state = 0;
				return this.arr[this.row].charAt(this.column);
			}
		}
	}
	private void back() {
		this.column--;
	}
	private boolean isLetter(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	private boolean isDigit(char c) {
		return c >= '0' && c <= '9';
	}
	private boolean isOperator(char c) {
		return c == '>' || c == '<' || c == '!';
	}
	private boolean isAssign(char c) {
		return c == '=';
	}
	private boolean isSpace(char c) {
		return c == ' ' || c == '\n' || c == '\t' || c == '\r';
	}
	private boolean isUnderscore(char c) {
		return c == '_';
	}
	private boolean isCommentary(char c){
		return c == '#';
	}
	private boolean isSum(char c){
		return c == '+';
	}
	private boolean isSubtraction(char c){
		return c == '-';
	}
	private boolean isMultiplication(char c){
		return c == '*';
	}
	private boolean isDivision(char c){
		return c == '/';
	}
	private boolean isLeftParenthesis(char c){
		return c == '(';
	}
	private boolean isRightParenthesis(char c){
		return c == ')';
	}
	private boolean isReservedWord(String token){
		return KEYWORDS.contains(token);
	}

	private boolean isEOF() {
		if (getCurrentLength() >= this.dataLength) {
			return true;
		}
		return false;
	}
	private int getCurrentLength(){
		int totalLength = 0, i = 0;
		while(i < this.row){
			totalLength += this.arr[i].length();
			i++;
		}
		return totalLength+this.column;
	}
	private int getDataLength(){
		int dataLength = 0;
		for(String s: this.arr){
			dataLength+= s.length();
		}
		return dataLength;
	}
}