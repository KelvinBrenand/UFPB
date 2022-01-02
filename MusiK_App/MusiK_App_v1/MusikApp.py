import pymysql
import winsound
import os
import time

clear = lambda: os.system('cls')
conexao = pymysql.connect(host= 'localhost',user= 'root',passwd= '0w3vDnEd6aR4',database= 'musikapp')
cursor = conexao.cursor()
def login():
    clear()
    global user
    print("----------LOGIN----------")
    print("Digite seu email:\n")
    user = str(input())
    cursor.execute("SELECT Email FROM usuario WHERE Email = %s", (user))
    resultado = cursor.fetchone()
    if resultado == None:
        print("Usuario não Cadastrado.\n""Redirecionando para página de cadastro:\n")
        time.sleep(3)
        cadastro()
    print("Digite sua senha:\n")
    senha = str(input())
    cursor.execute("SELECT senha FROM usuario WHERE senha = %s", (senha))
    result = cursor.fetchone()
    if result == None:
        print("Senha incorreta.\n")
        time.sleep(3)
        login()
    else:
        principal()
def cadastro():
    clear()
    print("----------CADASTRO----------")
    print("digite seu nome de usuario:\n")
    nome = str(input())
    print("digite seu email:\n")
    email = str(input())
    print("digite uma senha:\n")
    senha = str(input())
    print("digite sua idade:\n")
    idade = str(input())
    print("digite seu sexo ('M','F'):\n")
    sexo = str(input())
    print("digite seu país:\n")
    pais = str(input())
    com_sql = "INSERT INTO usuario(Nome, Email, Senha, Idade, Sexo, Pais) VALUES(%s,%s,%s,%s,%s,%s)"
    cursor.execute(com_sql, (nome, email, senha, idade, sexo, pais))
    conexao.commit()
    print(cursor.rowcount, "Usuário cadastrado com sucesso!\n")
    time.sleep(3)
    login()
def editaUsuario():
    clear()
    print("----------CONFIGURAÇÕES DE USUÁRIO----------")
    print("Editar Nome(1), Senha(2), Idade(3), País(4):\n")
    alt = int(input())
    if alt != 1 and alt != 2 and alt != 3 and alt != 4:
        print("ERROR!\n")
        time.sleep(3)
        principal()
    if alt == 1:
        modify = str(input("Digite seu nome:\n"))
        cursor.execute("UPDATE usuario SET Nome = %s WHERE Email = %s", (modify, user))
        print("Nome editado com sucesso.\n")
        conexao.commit()
        time.sleep(3)
        principal()
    if alt == 2:
        modify = str(input("Digite sua nova senha:\n"))
        cursor.execute("UPDATE usuario SET Senha = %s WHERE Email = %s", (modify, user))
        print("Senha editada com sucesso.\n")
        conexao.commit()
        time.sleep(3)
        principal()
    if alt == 3:
        modify = str(input("Digite sua idade:\n"))
        cursor.execute("UPDATE usuario SET Idade = %s WHERE Email = %s", (modify, user))
        print("Idade editada com sucesso.\n")
        conexao.commit()
        time.sleep(3)
        principal()
    if alt == 4:
        modify = str(input("Digite seu País:\n"))
        cursor.execute("UPDATE usuario SET Pais = %s WHERE Email = %s", (modify, user))
        print("País editado com sucesso.\n")
        conexao.commit()
        time.sleep(3)
        principal()
def criarPl():
    clear()
    print("----------CRIAÇÃO DE PLAYLIST----------")
    print("Digite o nome da playlist:\n")
    nome = str(input())
    print("Digite a privacidade da playlist(0,1):\n")
    privacidade = str(input())
    com_sql = "INSERT INTO playlist(Nome, Privacidade, Numero_de_reproducoes, Usuario_Email) VALUES(%s,%s,%s,%s)"
    cursor.execute(com_sql, (nome, privacidade, "0", user))
    conexao.commit()
    print(cursor.rowcount, "Playlist criada com sucesso!\n")
    time.sleep(3)
    principal()
def editaPl():
    clear()
    print("----------CONFIGURAÇÕES DE PLAYLIST----------")
    print("Digite o nome da playlist a ser editada:\n")
    PlPesq = str(input())
    cursor.execute("SELECT ID FROM playlist WHERE nome = %s", (PlPesq))
    resultPesq = cursor.fetchone()
    if resultPesq == None:
        print("Playlist não encontrada!\n")
        time.sleep(3)
        principal()
    else:
        print("Editar Nome(1), Privacidade(2):\n")
        alt = int(input())
        if alt != 1 and alt != 2:
            print("ERROR!\n")
            time.sleep(3)
            principal()
        if alt == 1:
            modify = str(input("Digite o novo nome:\n"))
            cursor.execute("UPDATE playlist SET Nome = %s WHERE ID = %s", (modify, resultPesq[0]))
            print("Nome editado com sucesso.\n")
            time.sleep(3)
            conexao.commit()
            principal()
        if alt == 2:
            modify = str(input("Digite a nova privacidade (0,1):\n"))
            cursor.execute("UPDATE playlist SET Privacidade = %s WHERE ID = %s", (modify, resultPesq[0]))
            print("Privacidade editada com sucesso.\n")
            time.sleep(3)
            conexao.commit()
            principal()
def AddMusicaPl():
    clear()
    print("----------ADD MÚSICAS EM PLAYLIST----------")
    print("Digite o nome da playlist na qual voce quer adicionar músicas:\n")
    plNome = input()
    cursor.execute("SELECT ID FROM playlist WHERE Nome = %s", (plNome))
    resultadoPl = cursor.fetchone()
    if resultadoPl == None:
        print("Playlist não encontrada.\n")
        time.sleep(3)
        principal()
    else:
        print("Digite a música a ser inserida na playlist:\n")
        musicaPesq = str(input())
        cursor.execute("SELECT ID FROM musica WHERE Nome = %s", (musicaPesq))
        resultPesq = cursor.fetchone()
        if resultPesq == None:
            print("Música não encontrada!\n")
            time.sleep(3)
            principal()
        else:
            com_sql = "INSERT INTO contem(Playlist_ID, Musica_ID) VALUES(%s,%s)"
            cursor.execute(com_sql, (resultadoPl, resultPesq))
            conexao.commit()
            print("Música adicionada com sucesso.\n")
            time.sleep(3)
            principal()
def pesquisaM():
    clear()
    print("----------REPRODUZIR MÚSICA----------")
    print("Digite a música a ser buscada:\n")
    musicaPesq = str(input())
    cursor.execute("SELECT ID FROM musica WHERE Nome = %s", (musicaPesq))
    resultPesq = cursor.fetchone()
    if resultPesq == None:
        print("Música não encontrada!\n")
        time.sleep(3)
        principal()
    else:
        print("\nReproduzindo música...\nPressione s para sair.\n")
        winsound.PlaySound('Music/'+musicaPesq+'.wav', winsound.SND_ASYNC | winsound.SND_ALIAS)
        cursor.execute("SELECT Numero_de_reproducoes FROM musica WHERE Nome = %s", (musicaPesq))
        nreprod = cursor.fetchone()
        nreprod = nreprod[0]+1
        cursor.execute("UPDATE musica SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, musicaPesq))
        conexao.commit()
        opcao = input()
        if opcao == 's':
            winsound.PlaySound(None, winsound.SND_ASYNC)
            principal()
def pesquisaPl():
    clear()
    print("----------REPRODUÇÃO DE PLAYLIST----------")
    print("Digite o nome da playlist a ser buscada:\n")
    PlPesq = str(input())
    cursor.execute("SELECT ID FROM playlist WHERE nome = %s", (PlPesq))
    resultPesq = cursor.fetchone()
    if resultPesq == None:
        print("Playlist não encontrada!\n")
        time.sleep(3)
        principal()
    else:
        cursor.execute("SELECT Musica_ID FROM contem WHERE Playlist_ID = %s", (resultPesq[0]))
        myresult = cursor.fetchall()
        print("Reproduzindo playlist...\n")
        for x in myresult:
            cursor.execute("SELECT Nome FROM musica WHERE ID = %s", (x[0]))
            myresult = cursor.fetchone()
            winsound.PlaySound('Music/'+myresult[0]+'.wav', winsound.SND_FILENAME)
            cursor.execute("SELECT Numero_de_reproducoes FROM musica WHERE Nome = %s", (myresult[0]))
            nreprod = cursor.fetchone()
            nreprod = nreprod[0]+1
            cursor.execute("UPDATE musica SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, myresult[0]))
            conexao.commit()
        print("Playlist finalizada.\nRedirecionando para a página principal.\n")
        cursor.execute("SELECT Numero_de_reproducoes FROM playlist WHERE Nome = %s", (PlPesq))
        nreprod = cursor.fetchone()
        nreprod = nreprod[0]+1
        cursor.execute("UPDATE playlist SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, PlPesq))
        conexao.commit()
        time.sleep(3)
        principal()
def pesquisaAlbum():
    clear()
    print("----------REPRODUÇÃO DE ÁLBUNS----------")
    print("Digite o nome do álbum a ser buscado:\n")
    PlPesq = str(input())
    cursor.execute("SELECT ID FROM album WHERE nome = %s", (PlPesq))
    resultPesq = cursor.fetchone()
    if resultPesq == None:
        print("Álbum não encontrado!\n")
        time.sleep(3)
        principal()
    else:
        cursor.execute("SELECT ID FROM musica WHERE Album_ID = %s", (resultPesq[0]))
        myresult = cursor.fetchall()
        print("Reproduzindo álbum...\n")
        for x in myresult:
            cursor.execute("SELECT Nome FROM musica WHERE ID = %s", (x[0]))
            myresult = cursor.fetchone()
            winsound.PlaySound('Music/'+myresult[0]+'.wav', winsound.SND_FILENAME)
            cursor.execute("SELECT Numero_de_reproducoes FROM musica WHERE Nome = %s", (myresult[0]))
            nreprod = cursor.fetchone()
            nreprod = nreprod[0]+1
            cursor.execute("UPDATE musica SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, myresult[0]))
            conexao.commit()
        print("Álbum finalizado.\nRedirecionando para a página principal.\n")
        time.sleep(3)
        principal()
def listaMusic():
    clear()
    print("----------LISTA DE MUSICAS----------")
    cursor.execute("SELECT nome FROM musica")
    myresult = cursor.fetchall()
    for x in myresult:
        print(x[0])
    print("\nPressione s para sair.\n")
    opcao = input()
    if opcao == 's':
        principal()
def listaAlbum():
    clear()
    print("----------LISTA DE ALBUNS----------")
    cursor.execute("SELECT nome FROM album")
    myresult = cursor.fetchall()
    for x in myresult:
        print(x[0])
    print("\nPressione s para sair.\n")
    opcao = input()
    if opcao == 's':
        principal()
def listaPl():
    clear()
    print("----------LISTA DE SUAS PLAYLIST----------")
    cursor.execute("SELECT nome FROM playlist WHERE Usuario_email=%s",(user))
    myresult = cursor.fetchall()
    for x in myresult:
        print(x[0])
    print("\nPressione s para sair.\n")
    opcao = input()
    if opcao == 's':
        principal()
def principal():
    clear()
    print("----------TELA PRINCIPAL----------")
    print("FUNÇÕES:\n"
        "1 - Listar músicas\n"
        "2 - Ouvir música\n"
        "3 - Listar Albuns\n"
        "4 - Ouvir álbum\n"
        "5 - Listar suas playlists\n"
        "6 - Ouvir playlist\n"
        "7 - Criar playlist\n"
        "8 - Editar playlist\n"
        "9 - Add música para playlist\n"
        "10 - Editar usuário\n"
        "11 - Sair\n")
    funcoes = int(input())
    if funcoes < 1 and funcoes > 10:
        print("Erro opção invalida!")
        time.sleep(3)
        principal()
    if funcoes == 1:
        listaMusic()
    if funcoes == 2:
        pesquisaM()
    if funcoes == 3:
        listaAlbum()
    if funcoes == 4:
        pesquisaAlbum()
    if funcoes == 5:
        listaPl()
    if funcoes == 6:
        pesquisaPl()
    if funcoes == 7:
        criarPl()
    if funcoes == 8:
        editaPl()
    if funcoes == 9:
        AddMusicaPl()
    if funcoes == 10:
        editaUsuario()
    if funcoes == 11:
        print("Encerrando app...")
        time.sleep(1)
        clear()
        exit()

clear()
print("----------MusiK----------")
print("1 - Fazer login")
print("2 - Criar Perfil")
perfil = int(input("\nO que deseja fazer?\n\n"))
if perfil != 1 and perfil != 2:
    print("Erro! Opção inválida.")
if perfil == 1:
    login()
if perfil == 2:
    cadastro()