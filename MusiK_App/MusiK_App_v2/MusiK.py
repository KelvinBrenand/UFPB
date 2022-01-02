import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication
from PyQt5.uic import loadUi
import pymysql
import winsound
import threading
import queue
import time

passwd = '0w3vDnEd6aR4'
conexao = pymysql.connect(host = 'localhost',user = 'root',passwd = passwd)
cursor = conexao.cursor()
cursor.execute("SHOW DATABASES LIKE 'MusikApp'")
resultado = cursor.fetchall()
if resultado == ():
    cursor.execute("CREATE DATABASE MusikApp")
    time.sleep(1)
    conexao = pymysql.connect(host= 'localhost',user= 'root',passwd= passwd,database= 'musikapp')
    cursor = conexao.cursor()
    cursor.execute("CREATE TABLE Usuario(Nome varchar(64) not null,Email varchar(128) not null primary key,Senha varchar(64) not null,Idade int not null,Sexo enum('M','F') not null,Pais varchar(64) not null)")
    cursor.execute("CREATE TABLE Playlist(ID int not null auto_increment primary key,Nome varchar(256) not null,Privacidade enum('0','1') not null,Numero_de_reproducoes int not null,Usuario_Email varchar(128) not null,foreign key (Usuario_Email) references Usuario(Email))")
    cursor.execute("CREATE TABLE Artista(ID int not null auto_increment primary key,Nome varchar(64) not null,Estilo varchar(64) not null)")
    cursor.execute("CREATE TABLE Album(ID int not null auto_increment primary key,Nome varchar(64) not null,Ano int not null,Estilo varchar(64) not null,Artista_ID int not null,foreign key (Artista_ID) references Artista(ID))")
    cursor.execute("CREATE TABLE Musica(ID int not null auto_increment primary key,Nome varchar(64) not null,Duracao int not null,Numero_de_reproducoes int not null,Album_ID int not null,foreign key (Album_ID) references Album(ID))")
    cursor.execute("CREATE TABLE Reproducao_PL(Usuario_Email varchar(128) not null,Playlist_ID int not null,foreign key (Usuario_Email) references Usuario(Email),foreign key (Playlist_ID) references Playlist(ID))")
    cursor.execute("CREATE TABLE Contem(Playlist_ID int not null,Musica_ID int not null,foreign key (Playlist_ID) references Playlist(ID),foreign key (Musica_ID) references Musica(ID))")
    cursor.execute("CREATE TABLE Reproducao_M(Usuario_Email varchar(128) not null,Musica_ID int not null,foreign key (Usuario_Email) references Usuario(Email),foreign key (Musica_ID) references Musica(ID))")
    time.sleep(1)
    Artista_Nome = ("MGMT","Charlie Brown Jr.","The White Buffalo","Gotye","M83","Alceu Valença","Sabaton","Herms Niel")
    Artista_Estilo = ("Rock","Alternative Rock","Alternative Country","Indie Rock","Eletronic","MPB","Heavy Metal","Military Songs")
    com_sql = "INSERT INTO artista(Nome, Estilo) VALUES(%s,%s)"
    for i in range(len(Artista_Nome)):
        cursor.execute(com_sql,(Artista_Nome[i], Artista_Estilo[i]))
    conexao.commit()

    Album_Nome = ("Little Dark Age","Abalando a Sua Fábrica","Once Upon a Time in the West","Making Mirrors","Hurry Up, We're Dreaming","Sete Desejos","The Last Stand","Erika")
    Album_Ano = ("2018","2001","2012","2011","2011","1992","2016","1930")
    Album_Estilo = ("Synth-pop","Pop","Country","Art Pop","Pop","Pop","Heavy metal","Marching Song")
    com_sql = "INSERT INTO Album(Nome, Ano, Estilo, Artista_ID) VALUES(%s,%s,%s,%s)"
    for i in range(len(Album_Nome)):
        cursor.execute("SELECT ID FROM Artista WHERE Nome = %s", (Artista_Nome[i]))
        resultado = cursor.fetchone()
        cursor.execute(com_sql,(Album_Nome[i], Album_Ano[i], Album_Estilo[i], str(resultado[0])))
    conexao.commit()

    com_sql = "INSERT INTO musica(Nome, Duracao, Numero_de_reproducoes, Album_ID) VALUES(%s,%s,%s,%s)"
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Once Upon a Time in the West"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("The Pilot", "226", "0", str(resultado[0])))
    cursor.execute(com_sql,("The Bowery", "207", "0", str(resultado[0])))
    cursor.execute(com_sql,("Ballad of a Dead Man", "217", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Little Dark Age"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("Little Dark Age", "300", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Abalando a Sua Fábrica"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("Como Tudo Deve Ser", "274", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Making Mirrors"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("Somebody That I Used To Know", "244", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Hurry Up, We're Dreaming"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("Midnight City", "244", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Sete Desejos"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("La Belle de Jour", "480", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("The Last Stand"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("The Last Stand", "236", "0", str(resultado[0])))
    cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("Erika"))
    resultado = cursor.fetchone()
    cursor.execute(com_sql,("Erika", "180", "0", str(resultado[0])))
    conexao.commit()
    time.sleep(1)
conexao = pymysql.connect(host= 'localhost',user= 'root',passwd= passwd,database= 'musikapp')
cursor = conexao.cursor()
q = queue.Queue()
finish = False

class Login(QDialog):
    def __init__(self):
        super(Login, self).__init__()
        loadUi("UI/login.ui",self)
        self.signIn.clicked.connect(self.loginFunction)
        self.signUp.clicked.connect(self.goToCreate)
    def loginFunction(self):
        global email
        email = self.email.text()
        password = self.password.text()
        cursor.execute("SELECT Email FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        cursor.execute("SELECT senha FROM usuario WHERE senha = %s", (password))
        result = cursor.fetchone()
        if email == "" or password == "":
            self.error.setText("Please input all fields")
        elif resultado == None:
            self.error.setText("User not found")
        elif result == None:
            self.error.setText("Invalid password")
        else:
            createHome = Home()
            widget.addWidget(createHome)
            widget.setCurrentIndex(widget.currentIndex()+1)
    def goToCreate(self):
        createAcc = Account()
        widget.addWidget(createAcc)
        widget.setCurrentIndex(widget.currentIndex()+1)
class Account(QDialog):
    def __init__(self):
        super(Account, self).__init__()
        loadUi("UI/account.ui",self)
        self.createAccount.clicked.connect(self.accountFunction)
        self.back.clicked.connect(self.goToLogin)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
    def accountFunction(self):
        createName = self.createEmail.text()
        createEmail = self.createEmail.text()
        createPassword = self.createPassword.text()
        createAge = self.createAge.text()
        createCountry = self.createCountry.text()
        createGender = ''
        if self.male.isChecked():
            createGender = 'M'
        if self.female.isChecked():
            createGender = 'F'
        if createName == "" or createEmail == "" or createPassword == "" or createAge == "" or createCountry == "" or createGender == '':
            self.error.setText("Please input all fields")
        elif (not createAge.isnumeric()) or int(createAge) < 0 or int(createAge) > 100:
            self.error.setText("Wrong information")
        else:
            com_sql = "INSERT INTO usuario(Nome, Email, Senha, Idade, Sexo, Pais) VALUES(%s,%s,%s,%s,%s,%s)"
            cursor.execute(com_sql, (createName, createEmail, createPassword, createAge, createGender, createCountry))
            conexao.commit()
            createHome = Home()
            widget.addWidget(createHome)
            widget.setCurrentIndex(widget.currentIndex()+1)
    def goToLogin(self):
        createLogin = Login()
        widget.addWidget(createLogin)
        widget.setCurrentIndex(widget.currentIndex()+1)
class Home(QDialog):
    def __init__(self):
        super(Home, self).__init__()
        loadUi("UI/home.ui",self)
        self.settings.clicked.connect(self.goToSettings)
        self.settings.setStyleSheet("QPushButton{background-image: url(UI/Icons/settings.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/settings2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.musicas.clicked.connect(self.goToMusics)
        self.albuns.clicked.connect(self.goToAlbuns)
        self.playlists.clicked.connect(self.goToPlaylists)
    def goToSettings(self):
        createSettings = Settings()
        widget.addWidget(createSettings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToMusics(self):
        createMusicas = Musics()
        widget.addWidget(createMusicas)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToAlbuns(self):
        createAlbuns = Albums()
        widget.addWidget(createAlbuns)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToPlaylists(self):
        createPlaylists = Playlists()
        widget.addWidget(createPlaylists)
        widget.setCurrentIndex(widget.currentIndex()+1)
class Settings(QDialog):
    def __init__(self):
        super(Settings, self).__init__()
        loadUi("UI/settings.ui",self)
        self.back.clicked.connect(self.goToHome)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.changePassword.clicked.connect(self.goToChangePassword)
        self.changeAge.clicked.connect(self.goToChangeAge)
        self.changeGender.clicked.connect(self.goToChangeGender)
        self.changeCountry.clicked.connect(self.goToChangeCountry)
        self.changeName.clicked.connect(self.goToChangeName)
    def goToHome(self):
        createHome = Home()
        widget.addWidget(createHome)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangePassword(self):
        createChangePassword = ChangePassword()
        widget.addWidget(createChangePassword)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangeAge(self):
        createChangeAge = ChangeAge()
        widget.addWidget(createChangeAge)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangeGender(self):
        createChangeGender = ChangeGender()
        widget.addWidget(createChangeGender)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangeCountry(self):
        createChangeCountry = ChangeCountry()
        widget.addWidget(createChangeCountry)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangeName(self):
        changeName = ChangeName()
        widget.addWidget(changeName)
        widget.setCurrentIndex(widget.currentIndex()+1)
class ChangeName(QDialog):
    def __init__(self):
        super(ChangeName, self).__init__()
        loadUi("UI/changeName.ui",self)
        self.back.clicked.connect(self.goToSettings)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT Nome FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        self.oldName.setText(resultado[0])
    def goToSettings(self):
        settings = Settings()
        widget.addWidget(settings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newName = self.newName.text()
        if newName == "":
            self.error.setText("Please input all fields")
        else:
            cursor.execute("UPDATE usuario SET Nome = %s WHERE Email = %s", (newName, email))
            conexao.commit()
            settings = Settings()
            widget.addWidget(settings)
            widget.setCurrentIndex(widget.currentIndex()+1)
class ChangePassword(QDialog):
    def __init__(self):
        super(ChangePassword, self).__init__()
        loadUi("UI/changePassword.ui",self)
        self.back.clicked.connect(self.goToSettings)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT senha FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        self.oldPassword.setText(resultado[0])
    def goToSettings(self):
        createSettings = Settings()
        widget.addWidget(createSettings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newPassword = self.newPassword.text()
        if newPassword == "":
            self.error.setText("Please input all fields")
        else:
            cursor.execute("UPDATE usuario SET senha = %s WHERE Email = %s", (newPassword, email))
            conexao.commit()
            settings = Settings()
            widget.addWidget(settings)
            widget.setCurrentIndex(widget.currentIndex()+1)
class ChangeAge(QDialog):
    def __init__(self):
        super(ChangeAge, self).__init__()
        loadUi("UI/changeAge.ui",self)
        self.back.clicked.connect(self.goToSettings)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT idade FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        self.oldAge.setText(str(resultado[0]))
    def goToSettings(self):
        createSettings = Settings()
        widget.addWidget(createSettings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newAge = self.newAge.text()
        if newAge == "":
            self.error.setText("Please input all fields")
        elif (not newAge.isnumeric()) or int(newAge) < 0 or int(newAge) > 100:
            self.error.setText("Wrong information")
        else:
            cursor.execute("UPDATE usuario SET idade = %s WHERE Email = %s", (newAge, email))
            conexao.commit()
            settings = Settings()
            widget.addWidget(settings)
            widget.setCurrentIndex(widget.currentIndex()+1)
class ChangeGender(QDialog):
    def __init__(self):
        super(ChangeGender, self).__init__()
        loadUi("UI/changeGender.ui",self)
        self.back.clicked.connect(self.goToSettings)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT sexo FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        oldGender = ''
        if resultado[0] == 'M':
            oldGender = 'Male'
        if resultado[0] == 'F':
            oldGender = 'Female'
        self.oldGender.setText(oldGender)
    def goToSettings(self):
        createSettings = Settings()
        widget.addWidget(createSettings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newGender = ''
        if self.male.isChecked():
            newGender = 'M'
        if self.female.isChecked():
            newGender = 'F'
        if newGender == "":
            self.error.setText("Please input all fields")
        else:
            cursor.execute("UPDATE usuario SET sexo = %s WHERE Email = %s", (newGender, email))
            conexao.commit()
            settings = Settings()
            widget.addWidget(settings)
            widget.setCurrentIndex(widget.currentIndex()+1)
class ChangeCountry(QDialog):
    def __init__(self):
        super(ChangeCountry, self).__init__()
        loadUi("UI/changeCountry.ui",self)
        self.back.clicked.connect(self.goToSettings)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT pais FROM usuario WHERE Email = %s", (email))
        resultado = cursor.fetchone()
        self.oldCountry.setText(resultado[0])
    def goToSettings(self):
        createSettings = Settings()
        widget.addWidget(createSettings)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newCountry = self.newCountry.text()
        if newCountry == "":
            self.error.setText("Please input all fields")
        else:
            cursor.execute("UPDATE usuario SET pais = %s WHERE Email = %s", (newCountry, email))
            conexao.commit()
            settings = Settings()
            widget.addWidget(settings)
            widget.setCurrentIndex(widget.currentIndex()+1)
class Musics(QDialog):
    def __init__(self):
        super(Musics, self).__init__()
        loadUi("UI/musics.ui",self)
        self.back.clicked.connect(self.goToHome)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.play.clicked.connect(self.goToListen)
        self.play.setStyleSheet("QPushButton{background-image: url(UI/Icons/play.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/play2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        cursor.execute("SELECT nome FROM musica")
        musicName = cursor.fetchall()
        cursor.execute("SELECT Duracao FROM musica")
        duration = cursor.fetchall()
        cursor.execute("SELECT Album_ID FROM musica ORDER BY ID")
        albumID = cursor.fetchall()
        artistID = []
        artist = []
        formatedMusic = []
        for x in albumID:
            cursor.execute("SELECT Artista_ID FROM album WHERE ID=%s", x[0])
            artistID.append(cursor.fetchone())
        for x in artistID:
            cursor.execute("SELECT nome FROM artista WHERE ID=%s", x[0])
            artist.append(cursor.fetchone())
        for i in range(len(musicName)):
            formatedMusic.append(musicName[i][0]+" - "+artist[i][0]+" - "+hms(duration[i][0]))
        formatedMusic.sort()
        for i in range(len(formatedMusic)):
            self.listWidget.addItem(str(i+1)+". "+formatedMusic[i])
        self.listWidget.itemDoubleClicked.connect(self.goToListen)
    def goToHome(self):
        createHome = Home()
        widget.addWidget(createHome)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToListen(self):
        if self.listWidget.currentItem() == None:
            pass
        else:
            musicName = self.listWidget.currentItem().text()
            point1 = musicName.find(" ")
            point2 = musicName.find("-")
            musicName = musicName[point1+1:point2-1]
            createListen = ListenMusic(musicName)
            widget.addWidget(createListen)
            widget.setCurrentIndex(widget.currentIndex()+1)
def hms(seconds):
        m = seconds % 3600 // 60
        s = seconds % 3600 % 60
        return '{:02d}:{:02d}'.format(m, s)
class Albums(QDialog):
    def __init__(self):
        super(Albums, self).__init__()
        loadUi("UI/albums.ui",self)
        self.back.clicked.connect(self.goToHome)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.play.clicked.connect(self.goToListenAlbum)
        self.play.setStyleSheet("QPushButton{background-image: url(UI/Icons/play.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/play2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        cursor.execute("SELECT nome FROM album")
        albumName = cursor.fetchall()
        artistID = []
        artist = []
        formatedMusic = []
        for x in albumName:
            cursor.execute("SELECT Artista_ID FROM album WHERE nome=%s", x[0])
            artistID.append(cursor.fetchone())
        for x in artistID:
            cursor.execute("SELECT nome FROM artista WHERE ID=%s", x[0])
            artist.append(cursor.fetchone())
        for i in range(len(albumName)):
            formatedMusic.append(albumName[i][0]+" - "+artist[i][0])
        formatedMusic.sort()
        for i in range(len(formatedMusic)):
            self.listWidget.addItem(str(i+1)+". "+formatedMusic[i])
        self.listWidget.itemDoubleClicked.connect(self.goToListenAlbum)
    def goToHome(self):
        createHome = Home()
        widget.addWidget(createHome)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToListenAlbum(self):
        if self.listWidget.currentItem() == None:
            pass
        else:
            albumName = self.listWidget.currentItem().text()
            point1 = albumName.find(" ")
            point2 = albumName.find("-")
            albumName = albumName[point1+1:point2-1]
            createListenAlbum = ListenAlbum(albumName)
            widget.addWidget(createListenAlbum)
            widget.setCurrentIndex(widget.currentIndex()+1)
def thread_function():
        while True:
            sound = q.get()
            if sound != None:
                musicName = sound
                point1 = musicName.find("/")
                point2 = musicName.find(".")
                musicName = musicName[point1+1:point2]
                cursor.execute("SELECT Numero_de_reproducoes FROM musica WHERE Nome = %s", musicName)
                nreprod = cursor.fetchone()
                nreprod = nreprod[0]+1
                cursor.execute("UPDATE musica SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, musicName))
                conexao.commit()
                cursor.execute("SELECT duracao FROM musica WHERE Nome = %s", musicName)
                duracao = cursor.fetchone()
                duracao = duracao[0]
            if sound is None:
                break
            winsound.PlaySound(sound, winsound.SND_ASYNC | winsound.SND_ALIAS)
            i = 0
            while i < duracao:
                time.sleep(1)
                i = i+1
                if finish == True:
                    winsound.PlaySound(None, winsound.SND_ASYNC)
                    q.queue.clear()
                    return None        
class ListenAlbum(QDialog):
    def __init__(self, albumName):
        super(ListenAlbum, self).__init__()
        loadUi("UI/listenAlbum.ui",self)
        self.back.clicked.connect(self.goToListenAlbum)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        cursor.execute("SELECT ID FROM album WHERE nome=%s", albumName)
        albumID = cursor.fetchone()
        cursor.execute("SELECT nome FROM musica WHERE Album_ID=%s", albumID[0])
        musicas = cursor.fetchall()
        global t
        t = threading.Thread(target=thread_function)
        t.daemon = True
        t.start()
        for x in musicas:
            q.put('Music/'+x[0]+'.wav')
            time.sleep(0.005)
        q.put(None)
    def goToListenAlbum(self):
        global finish
        finish = True
        createAlbums = Albums()
        widget.addWidget(createAlbums)
        widget.setCurrentIndex(widget.currentIndex()+1)
        time.sleep(1)
        finish = False
class ListenMusic(QDialog):
    def __init__(self,musicName):
        super(ListenMusic, self).__init__()
        loadUi("UI/listenMusic.ui",self)
        self.back.clicked.connect(self.goToMusic)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        winsound.PlaySound('Music/'+musicName+'.wav', winsound.SND_ASYNC | winsound.SND_ALIAS)
        cursor.execute("SELECT Numero_de_reproducoes FROM musica WHERE Nome = %s", (musicName))
        nreprod = cursor.fetchone()
        nreprod = nreprod[0]+1
        cursor.execute("UPDATE musica SET Numero_de_reproducoes = %s WHERE Nome = %s", (nreprod, musicName))
        conexao.commit()
    def goToMusic(self):
        winsound.PlaySound(None, winsound.SND_ASYNC)
        createMusics = Musics()
        widget.addWidget(createMusics)
        widget.setCurrentIndex(widget.currentIndex()+1)
class Playlists(QDialog):
    def __init__(self):
        super(Playlists, self).__init__()
        loadUi("UI/playlists.ui",self)
        self.back.clicked.connect(self.goToHome)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.play.clicked.connect(self.goToListenPlaylist)
        self.play.setStyleSheet("QPushButton{background-image: url(UI/Icons/play.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/play2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.newPlaylist.clicked.connect(self.goToNewPlaylist)
        self.editPlaylist.clicked.connect(self.goToEditPlaylist)
        cursor.execute("SELECT nome FROM playlist")
        playlistName = cursor.fetchall()
        formatedMusic = []
        for i in range(len(playlistName)):
            formatedMusic.append(playlistName[i][0])
        formatedMusic.sort()
        for i in range(len(formatedMusic)):
            self.listWidget.addItem(str(i+1)+". "+formatedMusic[i])
        self.listWidget.itemDoubleClicked.connect(self.goToListenPlaylist)
    def goToHome(self):
        createHome = Home()
        widget.addWidget(createHome)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToListenPlaylist(self):
        if self.listWidget.currentItem() == None:
            pass
        else:
            playlistName = self.listWidget.currentItem().text()
            point1 = playlistName.find(" ")
            playlistName = playlistName[point1+1:]
            createListenPlaylist = ListenPlaylist(playlistName)
            widget.addWidget(createListenPlaylist)
            widget.setCurrentIndex(widget.currentIndex()+1)
    def goToNewPlaylist(self):
        newPlaylist = NewPlaylist()
        widget.addWidget(newPlaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToEditPlaylist(self):
        if self.listWidget.currentItem() == None:
            pass
        else:
            playlistName = self.listWidget.currentItem().text()
            point1 = playlistName.find(" ")
            playlistName = playlistName[point1+1:]
            editPlaylist = EditPlaylist(playlistName)
            widget.addWidget(editPlaylist)
            widget.setCurrentIndex(widget.currentIndex()+1)
class ListenPlaylist(QDialog):
    def __init__(self, playlistName):
        super(ListenPlaylist, self).__init__()
        loadUi("UI/listenPlaylist.ui",self)
        self.back.clicked.connect(self.goToPlaylists)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        cursor.execute("SELECT ID FROM playlist WHERE nome=%s", playlistName)
        playlistID = cursor.fetchone()
        cursor.execute("SELECT Musica_ID FROM contem WHERE Playlist_ID=%s", playlistID[0])
        musicasID = cursor.fetchall()
        musicNames = []
        for x in musicasID:
            cursor.execute("SELECT nome FROM musica WHERE ID=%s", x[0])
            musicNames.append(cursor.fetchone())
        global t
        t = threading.Thread(target=thread_function)
        t.daemon = True
        t.start()
        for x in musicNames:
            q.put('Music/'+str(x[0])+'.wav')
            time.sleep(0.005)
        q.put(None)
    def goToPlaylists(self):
        global finish
        finish = True
        createPlaylists = Playlists()
        widget.addWidget(createPlaylists)
        widget.setCurrentIndex(widget.currentIndex()+1)
        time.sleep(1)
        finish = False
class NewPlaylist(QDialog):
    def __init__(self):
        super(NewPlaylist, self).__init__()
        loadUi("UI/newPlaylist.ui",self)
        self.createPlaylist.clicked.connect(self.playlistFunction)
        self.back.clicked.connect(self.goToPlaylists)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
    def playlistFunction(self):
        playlistName = self.playlistName.text()
        privacy = ''
        if self.public_2.isChecked():
            privacy = '1'
        if self.private_2.isChecked():
            privacy = '0'
        if privacy == '' or playlistName == "":
            self.error.setText("Please input all fields")
        else:
            com_sql = "INSERT INTO playlist(Nome, Privacidade, Numero_de_reproducoes, Usuario_Email) VALUES(%s,%s,%s,%s)"
            cursor.execute(com_sql, (playlistName, privacy, "0", email))
            conexao.commit()
            self.goToPlaylists()
    def goToPlaylists(self):
        createPlaylists = Playlists()
        widget.addWidget(createPlaylists)
        widget.setCurrentIndex(widget.currentIndex()+1)
class EditPlaylist(QDialog):
    def __init__(self,playlistName):
        super(EditPlaylist, self).__init__()
        loadUi("UI/editPlaylist.ui",self)
        self.changeName.clicked.connect(self.goToChangeNamePlaylist)
        self.changePrivacy.clicked.connect(self.goToChangePrivacy)
        self.addMusicsToPlaylist.clicked.connect(self.goToAddMusicsToPlaylist)
        self.back.clicked.connect(self.goToPlaylists)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.playlistName = playlistName
    def goToChangeNamePlaylist(self):
        changeNamePLaylist = ChangeNamePlaylist(self.playlistName)
        widget.addWidget(changeNamePLaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToChangePrivacy(self):
        changePrivacy = ChangePrivacy(self.playlistName)
        widget.addWidget(changePrivacy)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToAddMusicsToPlaylist(self):
        addMusicsToPlaylist = AddMusicsToPlaylist(self.playlistName)
        widget.addWidget(addMusicsToPlaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def goToPlaylists(self):
        createPlaylists = Playlists()
        widget.addWidget(createPlaylists)
        widget.setCurrentIndex(widget.currentIndex()+1)
class ChangeNamePlaylist(QDialog):
    def __init__(self, playlistName):
        super(ChangeNamePlaylist, self).__init__()
        loadUi("UI/changeNamePLaylist.ui",self)
        self.back.clicked.connect(self.goToEditPlaylist)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        self.oldName.setText(playlistName)
        self.playlistName = playlistName
    def goToEditPlaylist(self):
        editPlaylist = EditPlaylist(self.playlistName)
        widget.addWidget(editPlaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        newName = self.newName.text()
        if newName == "":
            self.error.setText("Please input all fields")
        else:
            cursor.execute("SELECT ID FROM playlist WHERE Nome = %s", (self.playlistName))
            resultado = cursor.fetchone()
            cursor.execute("UPDATE playlist SET Nome = %s WHERE ID = %s", (newName, resultado[0]))
            conexao.commit()
            self.playlistName = newName
            self.goToEditPlaylist()
class ChangePrivacy(QDialog):
    def __init__(self, playlistName):
        super(ChangePrivacy, self).__init__()
        loadUi("UI/changePrivacy.ui",self)
        self.back.clicked.connect(self.goToEditPlaylist)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.confirm.clicked.connect(self.confirmFunction)
        cursor.execute("SELECT Privacidade FROM playlist WHERE Nome = %s", playlistName)
        resultado = cursor.fetchone()
        privacy = ''
        if resultado[0] == '0':
            privacy = 'Private'
        if resultado[0] == '1':
            privacy = 'Public'
        self.oldPrivacy.setText(privacy)
        self.playlistName = playlistName
    def goToEditPlaylist(self):
        editPlaylist = EditPlaylist(self.playlistName)
        widget.addWidget(editPlaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def confirmFunction(self):
        privacy = ''
        if self.public_2.isChecked():
            privacy = '1'
        if self.private_2.isChecked():
            privacy = '0'
        if privacy == '':
            self.error.setText("Please input all fields")
        else:
            cursor.execute("SELECT ID FROM playlist WHERE Nome = %s", (self.playlistName))
            resultado = cursor.fetchone()
            cursor.execute("UPDATE playlist SET Privacidade = %s WHERE ID = %s", (privacy, resultado[0]))
            conexao.commit()
            self.goToEditPlaylist()
class AddMusicsToPlaylist(QDialog):
    def __init__(self, playlistName):
        super(AddMusicsToPlaylist, self).__init__()
        loadUi("UI/addMusic.ui",self)
        self.back.clicked.connect(self.goToEditPlaylist)
        self.back.setStyleSheet("QPushButton{background-image: url(UI/Icons/back.png); background-repeat: no-repeat; background-position: center; border-radius:5px; background-color: rgb(33, 33, 33);} QPushButton:pressed{background-image: url(UI/Icons/back2.png); background-repeat: no-repeat; background-position: center; background-color:rgb(66, 66, 66);}")
        self.addToPlaylist.clicked.connect(self.addMusicFunction)
        self.playlistName = playlistName
        cursor.execute("SELECT nome FROM musica")
        musicName = cursor.fetchall()
        cursor.execute("SELECT Duracao FROM musica")
        duration = cursor.fetchall()
        cursor.execute("SELECT Album_ID FROM musica ORDER BY ID")
        albumID = cursor.fetchall()
        artistID = []
        artist = []
        formatedMusic = []
        for x in albumID:
            cursor.execute("SELECT Artista_ID FROM album WHERE ID=%s", x[0])
            artistID.append(cursor.fetchone())
        for x in artistID:
            cursor.execute("SELECT nome FROM artista WHERE ID=%s", x[0])
            artist.append(cursor.fetchone())
        for i in range(len(musicName)):
            formatedMusic.append(musicName[i][0]+" - "+artist[i][0]+" - "+hms(duration[i][0]))
        formatedMusic.sort()
        for i in range(len(formatedMusic)):
            self.listWidget.addItem(str(i+1)+". "+formatedMusic[i])
        self.listWidget.itemDoubleClicked.connect(self.addMusicFunction)
    def goToEditPlaylist(self):
        editPlaylist = EditPlaylist(self.playlistName)
        widget.addWidget(editPlaylist)
        widget.setCurrentIndex(widget.currentIndex()+1)
    def addMusicFunction(self):
        if self.listWidget.currentItem() == None:
            pass
        else:
            musicName = self.listWidget.currentItem().text()
            point1 = musicName.find(" ")
            point2 = musicName.find("-")
            musicName = musicName[point1+1:point2-1]
            cursor.execute("SELECT ID FROM musica WHERE Nome = %s", (musicName))
            musicID = cursor.fetchone()
            cursor.execute("SELECT ID FROM playlist WHERE nome=%s", self.playlistName)
            playlistID = cursor.fetchone()
            com_sql = "INSERT INTO contem(Playlist_ID, Musica_ID) VALUES(%s,%s)"
            cursor.execute(com_sql, (playlistID[0], musicID[0]))
            conexao.commit()
            self.goToEditPlaylist()

app = QApplication(sys.argv)
mainWindow = Login()
widget = QtWidgets.QStackedWidget()
widget.addWidget(mainWindow)
widget.show()
app.exec_()
