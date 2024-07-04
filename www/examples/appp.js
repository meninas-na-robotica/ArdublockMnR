// Função para carregar o JSON
function loadJSON(callback) {
    fetch('examples.json')
        .then(response => response.json())  // Corrigido de 'response.tejson()' para 'response.json()'
        .then(data => callback(data))
        .catch(error => console.error('Error loading JSON:', error));
}

// Função para renderizar os exemplos
function renderExamples(examples) {
    examples.forEach(example => {
        if (example.visible) {
            const element = document.createElement('div');
            if (example.is_link) {
                const link = document.createElement('a');
                link.href = example.source_url;
                link.textContent = example.source_text;
                link.target = "_blank";  // Abre o link em uma nova aba
                element.appendChild(link);
            } else {
                element.textContent = example.source_text;
                // Aqui você pode adicionar o comportamento padrão para outros exemplos
                // Exemplo:
                // element.addEventListener('click', () => {
                //     restartApplicationWithExample(example.source_url);
                // });
            }
            document.body.appendChild(element);
        }
    });
}

// Chamar a função para carregar e renderizar os exemplos quando o DOM estiver carregado
document.addEventListener("DOMContentLoaded", function() {
    loadJSON(renderExamples);
});
