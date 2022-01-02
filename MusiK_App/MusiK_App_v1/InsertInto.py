import pymysql

conexao = pymysql.connect(host = 'localhost',user = 'root',passwd = '0w3vDnEd6aR4',database = 'MusikApp')
cursor = conexao.cursor()

Artista_Nome = ("MGMT","Charlie Brown Jr.","The White Buffalo","Gotye","M83","Alceu Valença","Sabaton","Herms Niel")
Artista_Estilo = ("Rock","Alternative Rock","Alternative Country","Indie Rock","Eletronic","MPB","Heavy Metal","Military Songs")
com_sql = "INSERT INTO artista(Nome, Estilo) VALUES(%s,%s)"
for i in range(len(Artista_Nome)):
    cursor.execute(com_sql,(Artista_Nome[i], Artista_Estilo[i]))
conexao.commit()

Album_Nome = ("Little Dark Age","100% Charlie Brown Jr. - Abalando a Sua Fábrica","Once Upon a Time in the West","Making Mirrors","Hurry Up, We're Dreaming","Sete Desejos","The Last Stand","Erika")
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
cursor.execute("SELECT ID FROM Album WHERE Nome = %s", ("100% Charlie Brown Jr. - Abalando a Sua Fábrica"))
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
#select * from artista; (no editor do mysql)