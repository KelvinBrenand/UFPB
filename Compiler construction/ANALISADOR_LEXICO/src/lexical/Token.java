package lexical;

import utils.TokenType;

public class Token {
	TokenType type;
	private String content;

	public Token(TokenType type, String content) {
		super();
		this.type = type;
		this.content = content;
	}
	public TokenType getType() {
		return type;
	}
	public void setType(TokenType type) {
		this.type = type;
	}
	public String getContent() {
		return content;
	}
	public void setContent(String content) {
		this.content = content;
	}
	@Override
	public String toString() {
		return "Token [type = " + type + ", content = " + content + "]";
	}
}
