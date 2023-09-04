window.onload = () => {
    document.getElementsByTagName('form')[0].addEventListener('submit', (event) => {
        event.preventDefault();

        const cuvant = document.getElementsByName('cuvant')[0].value;
        const option = document.getElementsByName('tip')[0].value;

        fetch('/', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ cuvant: cuvant, option: option })
        })
            .then(response => response.json())
            .then(data => {
                document.getElementsByName('iframe')[0].srcdoc = data.rezultat;
            })
            .catch(err => console.log(err));
    });
}