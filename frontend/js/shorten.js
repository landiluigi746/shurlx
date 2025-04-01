const form = document.getElementById("url-form");
const urlInput = document.getElementById("url-input");
const resultText = document.getElementById("result-text");
const shortenedURLText = document.getElementById("shortenedURL-text");

console.log("stronzo");

form.addEventListener("submit", (event) => {
  event.preventDefault();
  console.log("cazzo");

  const url = urlInput.value;

  resultText.style.display = "block";

  if (url === "" || url === undefined) {
    resultText.innerHTML = "You have to put an URL!";
    return;
  }

  console.log(url);

  fetch("http://localhost:8080" + `?url=${url}`, {
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
      shortenedURLText.href = `http://localhost:8080/${shortenedURL}`;
      shortenedURLText.innerText = `http://localhost:8080/${shortenedURL}`;
    })
    .catch((error) => {
      shortenedURLText.style.display = "none";

      resultText.innerText = "Sorry, there was an error!";
    });
});
