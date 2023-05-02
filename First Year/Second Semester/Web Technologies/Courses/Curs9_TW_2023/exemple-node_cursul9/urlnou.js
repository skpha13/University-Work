// Program ce ilustreaza procesarea URL-urilor
var adresa = new URL('http://TehniciWeb:8080/anulII/grupa232/?nume_student=Ionescu&nota_student=9');
var myURL=new URL("/foo/?p1=a&p2=b","http://example.com/");
//console.log(myURL);
console.log (adresa);
if (adresa.searchParams.get('nota_student') >= 5) {
  console.log ('Ai promovat examenul cu nota ' + adresa.searchParams.get('nota_student'));
} else {
  console.log ('Nu ai promovat examenul');
}
