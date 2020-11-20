#include "IDataBase.h"

using namespace std;
string _result_id;
list<Album> albums;
list<User> users;
list<Picture> pictures;
list<int> user_id_for_tags;

/*
This function open the db file and she success she create all the table if they not ealrdy exists
and return false if the file not opened.
*/
bool IDataBase::open()
{
	bool is_opened = true;
	int res = sqlite3_open(db_file_name.c_str(), &db);
	if (res != SQLITE_OK)
	{
		is_opened = false;
	}
	else
	{
		char* errMessage = nullptr;
		string str_statement = "CREATE TABLE IF NOT EXISTS USERS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,NAME TEXT);";
		int res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
		
		str_statement = "CREATE TABLE IF NOT EXISTS ALBUMS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,NAME TEXT,CREATION_DATE TEXT,USER_ID INTEGER REFERENCES USERS(ID));";
		res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
		
		str_statement = "CREATE TABLE IF NOT EXISTS PICTURES(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,NAME TEXT,LOCATION TEXT,CREATION_DATE TEXT,ALBUM_ID INTEGER REFERENCES ALBUMS(ID));";
		res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
		
		str_statement = "CREATE TABLE IF NOT EXISTS TAGS(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,PICTURE_ID INTEGER REFERENCES PICTURES(ID),USER_ID INTEGER REFERENCES USERS(ID));";
		res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);

	}
	return is_opened;
}

/*
This function close the data base in the end of the running.
*/
void IDataBase::close()
{
	sqlite3_close(db);
	db = nullptr;
}
/*
This function clear all the data in the tables.
*/
void IDataBase::clear()
{
	char* errMessage = nullptr;
	string str_statement = "DELETE FROM USERS;";
	int res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM ALBUMS;";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM PICTURES;";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM TAGS;";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}
//there is no memory that alloceted and because that the function do nothing.
void IDataBase::closeAlbum(Album & pAlbum)
{

}
//start of callback functions

/*
This callback function get the user id from tags table into list. 
*/
int get_user_id_for_tags_callback(void *unused, int count, char **data, char **columns)
{
	int i;
	for (i = 0; i < count; i++)
	{
		if (string(columns[i]) == "USER_ID")
		{
			user_id_for_tags.push_back(atoi(data[i]));
		}
	}
	return 0;
}
/*
This callback function get the data of the picture from pictures table and insert into list of pictures 
*/
int get_pictures_callback(void *unused, int count, char **data, char **columns)
{
	int i;
	Picture temp_picture(0,"");
	for (i = 0; i < count; i++)
	{
		if (string(columns[i]) == "ID")
		{
			temp_picture.setId(atoi(data[i]));
		}
		else if (string(columns[i]) == "NAME")
		{
			temp_picture.setName(string(data[i]));
		}
		else if (string(columns[i]) == "LOCATION")
		{
			temp_picture.setPath(string(data[i]));
		}
		else if (string(columns[i]) == "CREATION_DATE")
		{
			temp_picture.setCreationDate(string(data[i]));
		}
	}
	pictures.push_back(temp_picture);
	return 0;
}

/*
this callback function get the id/count/avg (all the things is a one number)
*/
int callback_to_get_id(void *unused, int count, char **data, char **columns)
{
	_result_id = data[0];
	return 0;
}
/*
This callback function get the data of the album from albums table and insert into list of albums
*/
int get_albums_callback(void *unused, int count, char **data, char **columns)
{
	int i;
	Album temp_album;
	for (i = 0; i < count; i++)
	{
		if (string(columns[i]) == "NAME")
		{
			temp_album.setName(string(data[i]));
		}
		else if (string(columns[i]) == "CREATION_DATE")
		{
			temp_album.setCreationDate(string(data[i]));
		}
		else if (string(columns[i]) == "USER_ID")
		{
			temp_album.setOwner(atoi(data[i]));
		}
	}
	albums.push_back(temp_album);
	return 0;
}

/*
This callback function get the data of the user from users table and insert into list of users
*/
int get_users_callback(void *unused, int count, char **data, char **columns)
{
	int i;
	User temp_user;
	for (i = 0; i < count; i++)
	{
		if (string(columns[i]) == "ID")
		{
			temp_user.setId(atoi(data[i]));
		}
		else if (string(columns[i]) == "NAME")
		{
			temp_user.setName(data[i]);
		}
	}
	users.push_back(temp_user);
	return 0;
}
//end of callback functions

/*
This function input a type(users or pictures) and check what the last (and biggest) id that used
and if the table is empty she start with the defult and first id (for user is 200 and for picture is 100)
*/
int IDataBase::get_next_id(std::string type)
{
	char* errMessage = nullptr;
	int next_id = 200;
	string str_statement = "SELECT COUNT(ID) FROM " + type + ";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	if(atoi(_result_id.c_str())>0)
	{
		str_statement = "SELECT MAX(ID) FROM " + type + ";";
		res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
		next_id = atoi(_result_id.c_str());
	}
	else if (type == "PICTURES")
	{
		next_id = 100;
	}
	return next_id;
}
/*
This function used with the global verible albums and get the picture and the tags of picture that belong to him.
*/
void IDataBase::get_albums_helper()
{
	char* errMessage = nullptr;
	pictures.clear();
	user_id_for_tags.clear();
	for (Album& album : albums)
	{
		string str_statement = "SELECT PICTURES.ID,PICTURES.NAME,LOCATION,PICTURES.CREATION_DATE FROM PICTURES INNER JOIN ALBUMS ON PICTURES.ALBUM_ID=ALBUMS.ID WHERE ALBUMS.NAME='" + album.getName() + "';";
		int res = sqlite3_exec(db, str_statement.c_str(), get_pictures_callback, nullptr, &errMessage);
		for (Picture& picture : pictures)
		{
			str_statement = "SELECT USER_ID FROM TAGS WHERE PICTURE_ID=" + to_string(picture.getId()) + ";";
			res = sqlite3_exec(db, str_statement.c_str(), get_user_id_for_tags_callback, nullptr, &errMessage);
			for (int& user_id : user_id_for_tags)
			{
				picture.tagUser(user_id);
			}
			album.addPicture(picture);
		}
	}
}
/*
print all the albums
*/
void IDataBase::printAlbums()
{
	list<Album> d_albums = getAlbums();
	if (d_albums.empty()) {
		throw MyException("There are no existing albums.");
	}
	std::cout << "Album list:" << std::endl;
	std::cout << "-----------" << std::endl;
	for (const Album& album : getAlbums())
	{
		std::cout << std::setw(5) << "* " << album << album.getCreationDate();
	}
}
/*
return all the albums.
*/
const std::list<Album> IDataBase::getAlbums()
{
	albums.clear();
	string str_statement = "SELECT * FROM ALBUMS;";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, str_statement.c_str(), get_albums_callback, nullptr, &errMessage);
	get_albums_helper();
	return albums;
}
/*
return all the albums of spesific user that get in the input
*/
const std::list<Album> IDataBase::getAlbumsOfUser(const User & user)
{
	albums.clear();
	string str_statement = "SELECT * FROM ALBUMS WHERE USER_ID="+to_string(user.getId())+";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, str_statement.c_str(), get_albums_callback, nullptr, &errMessage);
	get_albums_helper();
	return albums;
}
/*
This function craete new album with the data that she get in the input.  
*/
void IDataBase::createAlbum(const Album & album)
{
	string str_statement = "INSERT INTO ALBUMS (NAME,CREATION_DATE,USER_ID) VALUES('"+album.getName()+"','"+album.getCreationDate()+"',"+to_string(album.getOwnerId())+");";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}
/*
This function delete album and all the picture and the tags that belong to him.
*/
void IDataBase::deleteAlbum(const std::string & albumName, int userId)
{
	char* errMessage = nullptr;
	//get album id
	string str_statement = "SELECT ID FROM ALBUMS WHERE NAME='"+albumName+"' AND USER_ID="+to_string(userId)+";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	//delete all the pictures (and the tags in the pictures) that in the album
	str_statement = "DELETE FROM TAGS WHERE USER_ID=" + to_string(userId) + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM PICTURES WHERE ALBUM_ID=" + _result_id + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM ALBUMS WHERE ID=" + _result_id + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function check if the album exist by count - if the count=0 the not exit and if the count=1 the album exist. 
*/
bool IDataBase::doesAlbumExists(const std::string & albumName, int userId)
{
	_result_id = "0";
	string str_statement = "SELECT COUNT(ID) FROM ALBUMS WHERE NAME='"+albumName+"' AND USER_ID="+to_string(userId)+";";
	char* errMessage = nullptr;
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	if (atoi(_result_id.c_str())==0)
	{
		return false;
	}
	return true;
}

/*
This function input the album name and get the data of the album and in the album from the tables and return the album
*/
Album IDataBase::openAlbum(const std::string & albumName)
{
	albums.clear();
	pictures.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT * FROM ALBUMS WHERE NAME='"+albumName+"';";
	int res = sqlite3_exec(db, str_statement.c_str(), get_albums_callback, nullptr, &errMessage);
	if (albums.empty())
	{
		throw MyException("No album with name " + albumName + " exists");
	}
	Album o_album = *(albums.begin());
	str_statement = "SELECT ID FROM ALBUMS WHERE NAME='" + albumName + "';";
	res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "SELECT * FROM PICTURES WHERE ALBUM_ID=" +_result_id+";";
	res = sqlite3_exec(db, str_statement.c_str(), get_pictures_callback, nullptr, &errMessage);
	for (Picture& picture : pictures)
	{
		str_statement = "SELECT * FROM TAGS WHERE PICTURE_ID="+to_string(picture.getId())+";";
		res = sqlite3_exec(db, str_statement.c_str(), get_user_id_for_tags_callback, nullptr, &errMessage);
		for (int& user_id : user_id_for_tags)
		{
			picture.tagUser(user_id);
		}
		o_album.addPicture(picture);
	}
	albums.clear();
	return o_album;
}

/*
This function add picture to his table (by get the id of album with the album name)
*/
void IDataBase::addPictureToAlbumByName(const std::string & albumName, const Picture & picture)
{
	char* errMessage = nullptr;
	string str_statement = "SELECT ID FROM ALBUMS WHERE NAME='" + albumName + "';";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "INSERT INTO PICTURES (ID,NAME,LOCATION,CREATION_DATE,ALBUM_ID) VALUES("+ to_string(picture.getId())+",'"+ picture.getName()+"','"+ picture.getPath()+"','"+ picture.getCreationDate()+"',"+_result_id+");";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function input album name of the picture and picture name remove picture from his table.
*/
void IDataBase::removePictureFromAlbumByName(const std::string & albumName, const std::string & pictureName)
{
	char* errMessage = nullptr;
	string str_statement = "SELECT ID FROM ALBUMS WHERE NAME='" + albumName + "';";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "DELETE FROM PICTURES WHERE NAME='"+pictureName+"' AND ALBUM_ID="+_result_id+";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function tag user in picture by add to tags table row with the user id and the picture id(get the album id by album name
and than get picture id by the picture name and the album id)
*/
void IDataBase::tagUserInPicture(const std::string & albumName, const std::string & pictureName, int userId)
{
	char* errMessage = nullptr;
	string str_statement = "SELECT ID FROM ALBUMS WHERE NAME='" + albumName + "' AND USER_ID="+to_string(userId)+";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "SELECT ID FROM PICTURES WHERE NAME='"+pictureName+"' AND ALBUM_ID="+_result_id+";";
	res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "INSERT INTO TAGS (PICTURE_ID,USER_ID) VALUES("+_result_id+","+to_string(userId)+");";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function untag user in picture by remove row with the user id and the picture id(get the album id by album name
and than get picture id by the picture name and the album id)
*/
void IDataBase::untagUserInPicture(const std::string & albumName, const std::string & pictureName, int userId)
{
	char* errMessage = nullptr;
	string str_statement = "SELECT ID FROM ALBUMS WHERE NAME='" + albumName + "';";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "SELECT ID FROM PICTURES WHERE NAME='" + pictureName + "'AND ALBUM_ID=" + _result_id + ";";
	res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "DELETE FROM TAGS WHERE PICTURE_ID="+_result_id+"USER_ID="+to_string(userId)+";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function print all the users.
*/
void IDataBase::printUsers()
{
	users.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT * FROM USERS";
	int res = sqlite3_exec(db, str_statement.c_str(), get_users_callback, nullptr, &errMessage);
	std::cout << "Users list:" << std::endl;
	std::cout << "-----------" << std::endl;
	for (const auto& user : users) 
	{
		std::cout << user << std::endl;
	}
	users.clear();
}

/*
This function craete user by add row to users table
*/
void IDataBase::createUser(User & user)
{
	char* errMessage = nullptr;
	string str_statement = "INSERT INTO USERS VALUES("+to_string(user.getId())+",'"+user.getName()+"');";
	int res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function delete user and all the albums,picture and tags that belong to him.
*/
void IDataBase::deleteUser(const User & user)
{
	char* errMessage = nullptr;
	string str_statement = "DELETE FROM USERS WHERE ID="+to_string(user.getId())+" AND NAME='"+user.getName()+"';";
	int res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM TAGS WHERE USER_ID=" + to_string(user.getId()) + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "SELECT ID FROM ALBUMS WHERE USER_ID="+ to_string(user.getId()) + ";";
	res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	str_statement = "DELETE FROM PICTURES WHERE ALBUM_ID=" + _result_id + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
	str_statement = "DELETE FROM ALBUMS WHERE USER_ID=" + to_string(user.getId()) + ";";
	res = sqlite3_exec(db, str_statement.c_str(), nullptr, nullptr, &errMessage);
}

/*
This function check if the user exists by try to get user witout exeption - if the get user does not
throw exeption she return true else she return false.
*/
bool IDataBase::doesUserExists(int userId)
{
	try
	{
		getUser(userId);
	}
	catch(ItemNotFoundException& e)
	{
		return false;
	}
	return true;
}

/*
This function get user from users table by the user id and return him but if there is no user with this user id
she throw exeption that user doesnt exists
*/
User IDataBase::getUser(int userId)
{
	users.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT * FROM USERS WHERE ID="+to_string(userId)+";";
	int res = sqlite3_exec(db, str_statement.c_str(), get_users_callback, nullptr, &errMessage);
	if (users.empty())
	{
		throw ItemNotFoundException("User", userId);
	}
	return (*users.begin());
}
/*
This function count how many albums owned to spesidic user that she get as a input
and return the count
*/
int IDataBase::countAlbumsOwnedOfUser(const User & user)
{
	_result_id = "0";
	char* errMessage = nullptr;
	string str_statement = "SELECT COUNT(ID) FROM ALBUMS WHERE USER_ID="+to_string(user.getId())+";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	return atoi(_result_id.c_str());
}
/*
This function count how many albums the spesific user is tagged and return the count  
*/
int IDataBase::countAlbumsTaggedOfUser(const User & user)
{
	_result_id = "0";
	char* errMessage = nullptr;
	string str_statement = "SELECT COUNT(ID) FROM TAGS WHERE USER_ID="+to_string(user.getId())+";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	return atoi(_result_id.c_str());
}
/*
This function return list of all the picture that the spesific user was tagged.
*/
std::list<Picture> IDataBase::getTaggedPicturesOfUser(const User & user)
{
	pictures.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT PICTURE_ID,NAME,LOCATION,CREATION_DATE FROM TAGS INNER JOIN PICTURES ON TAGS.PICTURE_ID=PICTURES.ID WHERE USER_ID=" + to_string(user.getId()) + ";";
	int res = sqlite3_exec(db, str_statement.c_str(), get_pictures_callback, nullptr, &errMessage);
	return pictures;
}
/*
This funtion count how many tags owned for the spesific user. 
*/
int IDataBase::countTagsOfUser(const User & user)
{
	_result_id = "0";
	char* errMessage = nullptr;
	string str_statement = "SELECT COUNT(ID) FROM TAGS WHERE USER_ID="+to_string(user.getId())+";";
	int res = sqlite3_exec(db, str_statement.c_str(), callback_to_get_id, nullptr, &errMessage);
	return atoi(_result_id.c_str());
}
/*
This function return the user that tagged more then enyone
*/
User IDataBase::getTopTaggedUser()
{
	users.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT NAME,USER_ID AS 'ID' FROM TAGS INNER JOIN USERS ON TAGS.USER_ID=USERS.ID GROUP BY USER_ID ORDER BY 'value_occurrence' DESC LIMIT 1;";
	int res = sqlite3_exec(db, str_statement.c_str(), get_users_callback, nullptr, &errMessage);
	if (users.empty())
	{
		throw MyException("There is no user tagged");
	}
	User topTaggedUser = *(users.begin());
	users.clear();
	return topTaggedUser;
}
/*
This function retunr the picture that tagged more then enyone
*/
Picture IDataBase::getTopTaggedPicture()
{
	pictures.clear();
	char* errMessage = nullptr;
	string str_statement = "SELECT NAME,LOCATION,CREATION_DATE,PICTURE_ID AS 'ID' FROM TAGS INNER JOIN PICTURES ON TAGS.PICTURE_ID=PICTURES.ID GROUP BY PICTURE_ID ORDER BY 'value_occurrence' DESC LIMIT 1;";
	int res = sqlite3_exec(db, str_statement.c_str(), get_pictures_callback, nullptr, &errMessage);
	if (pictures.empty())
	{
		throw MyException("There is no picture tagged");
	}
	Picture topTaggedPicture = *(pictures.begin());
	pictures.clear();
	return topTaggedPicture;
}
/*
This function calculte the average of the tags per album of spesific user
*/
float IDataBase::averageTagsPerAlbumOfUser(const User & user)
{
	int albumsTaggedCount = countAlbumsTaggedOfUser(user);

	if (0 == albumsTaggedCount) {
		return 0;
	}

	return static_cast<float>(countTagsOfUser(user)) / albumsTaggedCount;
}
