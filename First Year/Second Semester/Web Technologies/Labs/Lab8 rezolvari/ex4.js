window.onload=function(){

   setTimeout(colorare,2000);

  }

function colorare(){
  var butoane=document.getElementsByTagName("input");
  var i=0;
  var c=setInterval(function(){
    document.body.style.backgroundColor=butoane[i].value;
    butoane[i].checked=true;
    i=(i+1)%5;
  },3000);
  document.body.onclick=function(){
    clearInterval(c);
    alert(document.body.style.backgroundColor);
  }
}