import pymysql

conexao = pymysql.connect(host = 'localhost',user = 'root',passwd = '0w3vDnEd6aR4',database = 'MusikApp')
cursor = conexao.cursor()
cursor.execute("CREATE TABLE Usuario(Nome varchar(64) not null,Email varchar(128) not null primary key,Senha varchar(64) not null,Idade int not null,Sexo enum('M','F') not null,Pais varchar(64) not null)")
cursor.execute("CREATE TABLE Playlist(ID int not null auto_increment primary key,Nome varchar(256) not null,Privacidade enum('0','1') not null,Numero_de_reproducoes int not null,Usuario_Email varchar(128) not null,foreign key (Usuario_Email) references Usuario(Email))")
cursor.execute("CREATE TABLE Artista(ID int not null auto_increment primary key,Nome varchar(64) not null,Estilo varchar(64) not null)")
cursor.execute("CREATE TABLE Album(ID int not null auto_increment primary key,Nome varchar(64) not null,Ano int not null,Estilo varchar(64) not null,Artista_ID int not null,foreign key (Artista_ID) references Artista(ID))")
cursor.execute("CREATE TABLE Musica(ID int not null auto_increment primary key,Nome varchar(64) not null,Duracao int not null,Numero_de_reproducoes int not null,Album_ID int not null,foreign key (Album_ID) references Album(ID))")
cursor.execute("CREATE TABLE Reproducao_PL(Usuario_Email varchar(128) not null,Playlist_ID int not null,foreign key (Usuario_Email) references Usuario(Email),foreign key (Playlist_ID) references Playlist(ID))")
cursor.execute("CREATE TABLE Contem(Playlist_ID int not null,Musica_ID int not null,foreign key (Playlist_ID) references Playlist(ID),foreign key (Musica_ID) references Musica(ID))")
cursor.execute("CREATE TABLE Reproducao_M(Usuario_Email varchar(128) not null,Musica_ID int not null,foreign key (Usuario_Email) references Usuario(Email),foreign key (Musica_ID) references Musica(ID))")