
window.onload = myMain;

function myMain() {
 document.getElementById('buton').onmouseover = stil1;  // fara paranteze
 document.getElementById('buton').onmouseout = stil2;
}




function stil1() {
 
// document.getElementById('schimb').style.backgroundColor = "yellow"; 
 document.getElementById('schimb').className = "stil1"; //preferat
}
function stil2() { var s;
 //document.getElementById('schimb').style.backgroundColor = "white"; 
 document.getElementById('schimb').className = "stil2";

}



