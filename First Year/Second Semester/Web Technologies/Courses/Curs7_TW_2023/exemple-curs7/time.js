var pl=document.getElementsByTagName("p");
for(var i=0;i<pl.length;i++)
  setTimeout(function(culoare,ob){ ob.style.color=culoare;},3000*(i+1),"red",pl[i]);
//for(let i=0;i<pl.length;i++)
  //setTimeout(function(){colorare("red",pl[i]);},3000*(i+1));

function colorare(culoare,ob)
{
 ob.style.color=culoare;
}

