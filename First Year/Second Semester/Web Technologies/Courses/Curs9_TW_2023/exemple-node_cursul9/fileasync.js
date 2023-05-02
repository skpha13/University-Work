var fs = require('fs');
fs.readFile('date.txt','utf8',function (err, data) {

	if (err) console.log(err) ;
        console.log(data);


});
console.log("Citire asincrona");
