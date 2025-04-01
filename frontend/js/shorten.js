const form = document.getElementById("url-form");
const urlInput = document.getElementById("url-input");
const resultText = document.getElementById("result-text");
const shortenedURLText = document.getElementById("shortenedURL-text");

const BACKEND_URL = "http://localhost:8080";

form.addEventListener("submit", (event) => {
  event.preventDefault();

  const url = urlInput.value;

  resultText.style.display = "block";

  fetch(`${BACKEND_URL}?url=${url}`, {
    method: "POST",
    headers: {
      "Content-Type": "text/plain",
    },
  })
    .then((response) => {
      resultText.style.display = "block";

      if (response.ok) {
        shortenedURLText.style.display = "block";

        resultText.innerText = `Your shortened url:`;
        return response.text();
      }

      shortenedURLText.style.display = "none";

      switch (response.status) {
        case 400:
          resultText.innerHTML = "Sorry, the URL you sent is invalid.";
          break;
        case 500:
          resultText.innerHTML = "Sorry, the server encountered an error.";
          break;
      }
    })
    .then((shortenedURL) => {
      shortenedURLText.href = `${BACKEND_URL}/${shortenedURL}`;
      shortenedURLText.innerText = `${BACKEND_URL}/${shortenedURL}`;
    })
    .catch((error) => {
      shortenedURLText.style.display = "none";

      resultText.innerText = "Sorry, there was an error!";
    });
});
