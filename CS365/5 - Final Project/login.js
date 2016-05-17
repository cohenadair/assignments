var Login = function() {}

Login.prototype.getCollection = function(db) {
	return db.collection("checkerusers");
}

Login.prototype.userExists = function(db, user, callback) {
	Login.prototype.getCollection(db).findOne(user, function(err, user) {
		callback(user != null);
	});
};

// Adds a user to the given database
// Author: Kyle
// 
// callback: function(resultObject, msg)
Login.prototype.insertUser = function(db, whatUser, callback) {
	var collection = Login.prototype.getCollection(db);
	
	collection.findOne(whatUser, function(err, user) {
		if (user) {
			callback(null, "The username you entered already exists");
			return;
		}

		collection.insertOne(whatUser, function(err, result) {
			if (err != null) {
				console.log("ERR on attempting to insert()..." + err);
				callback(null, "Error signing up"); // "returning" null means we are telling the caller it didn't work.
			} else {	
				console.log("insert() succeeded.  User added! " );
				callback(result, "Signup successful"); // here we indicate success by returning the result object.
			}
		});
	});
};



Login.prototype.loginUser = function(db,whatUser,callback){
	var collection = Login.prototype.getCollection(db);
	
	collection.findOne(whatUser,function(err,user){
		if(user){
			callback(user,"Login Successful");
			
		}else{
			
			callback(null,"Can't login");
		}
	});

};

module.exports = new Login();
