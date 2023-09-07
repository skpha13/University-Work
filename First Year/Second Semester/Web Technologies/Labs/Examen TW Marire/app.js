window.onload = () => {
    document.getElementById('form').addEventListener('submit', (event) => {
        event.preventDefault();

        const option = document.getElementsByTagName('select')[0].value;
        const range = document.getElementsByTagName('input')[0].value;

        fetch('/', {
            method: "POST",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ option: option, range: range })
        })
            .then(response => response.json())
            .then(data => {
                document.getElementById('result').innerText = data.result;
            })
            .catch(err => console.log(err));
    });
}