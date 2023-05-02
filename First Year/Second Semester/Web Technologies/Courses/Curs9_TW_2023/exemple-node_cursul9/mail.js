var nodemailer = require('nodemailer');   //folosirea modulului nodemailer

var transporter = nodemailer.createTransport({         //face autentificarea
  service: 'gmail',
  auth: {
    user: 'my.mail.node@gmail.com',
    pass: 'parola'
  },
 tls:{rejectUnauthorized:false}

});

var mailOptions = {                               //optiunile mesajului
  from: 'my.mail.node@gmail.com',
  to: '.....',
  subject: 'Mesaj din Node.js',
  text: 'Hello!'
};

transporter.sendMail(mailOptions, function(error, info){              //trimite mail
  if (error) {
    console.log(error);
  } else {
    console.log('Mail trimis: ' + info.response);
  }
});
