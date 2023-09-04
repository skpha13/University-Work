window.onload = () => {
    document.getElementsByTagName('form')[0].addEventListener('submit', (event) => {
        event.preventDefault();

        const nume = document.getElementsByName('nume')[0].value;
        const nota1 = parseInt(document.getElementsByName('nota1')[0].value);
        const nota2 = parseInt(document.getElementsByName('nota2')[0].value);

        fetch('/form', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ nume: nume, nota1: nota1, nota2: nota2 })
        })
            .then(response => response.json())
            .then(data => {
                document.getElementsByName('iframe')[0].srcdoc = data.rezultat;

            })
            .catch(err => console.log(err));
    });
}