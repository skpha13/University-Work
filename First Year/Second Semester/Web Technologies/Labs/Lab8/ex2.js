window.onload = () => {
    document.addEventListener('click',function (event) {
       var d = document.createElement("div");
       d.className = "animat";
       var rand = Math.floor(Math.random()*2) + 1;
       d.style.animationName = "miscare" + rand.toString();
       d.style.position = "absolute";
       d.style.left = event.clientX + 'px';
       d.style.top = event.clientY + 'px';
       if(event.target.classList.contains("animat"))
       {return;}
       document.body.append(d);
    });
}