import pymysql

conexao = pymysql.connect(host = 'localhost',user = 'root',passwd = '0w3vDnEd6aR4')
cursor = conexao.cursor()
cursor.execute("CREATE DATABASE MusikApp")