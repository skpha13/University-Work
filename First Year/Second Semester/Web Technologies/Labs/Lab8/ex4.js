window.onload = () => {
    var intervalID = null;
    setTimeout(() => {
        var body = document.getElementsByTagName('body')[0];
        var radio = document.getElementsByName('culori');
        var index = 0;
        intervalID = setInterval(function(){
            radio[index].checked = !radio[index].checked;

            body.style.backgroundColor = radio[index].value;
            index++;
            if(index === radio.length) index = 0;
        },3000);
    },2000);

    document.addEventListener('click',function () {
        clearInterval(intervalID);
    });
}

