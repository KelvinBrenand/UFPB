package main;

import lexical.Scanner;
import lexical.Token;

public class Main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner("source_code.mc");
		Token token = null;
		do {
			token = scanner.nextToken();
			System.out.println(token);
		} while (token != null);
	}

}
