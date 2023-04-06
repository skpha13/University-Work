window.onload = () => {
    function getInfo() {
        const titlu = document.getElementById("titlu").value;
        const continut = document.getElementById("post").value;

        var article = document.createElement("article")
        const title = document.createElement("h3");
        const content = document.createElement("p");
        const date = document.createElement("span");

        const temp = new Date();
        date.innerText = " " + temp.getDate() + "/" + (temp.getMonth() + 1) + "/" + temp.getFullYear();

        content.innerText = continut;
        title.innerText = titlu;
        title.appendChild(date);

        article.appendChild(title);
        article.appendChild(content);

        article.className = "post";

        var postari = document.getElementById("postari");
        postari.appendChild(article);
    }

    var obj = document.getElementsByTagName("button");
    obj[0].addEventListener('click',() => {
        getInfo()

        const container = document.getElementsByClassName("post");
        for(const article of container) {
            article.addEventListener('dblclick', () => {
                article.remove();
            });
        }
    });
}
