const cat = document.getElementById("cat");
const flower = document.getElementById("flower");

document.addEventListener("keydown", function(event) {
  jump();  
});

function jump () {
    if (cat.classList != "jump") {
        cat.classList.add("jump")
    }
    setTimeout ( function() {
        cat.classList.remove("jump")
    }, 500)   
}

let isAlive = setInterval ( function() {
    let catTop = parseInt(window.getComputedStyle(cat).getPropertyValue("top"))
    let flowerLeft = parseInt(window.getComputedStyle(flower).getPropertyValue("left"))

    if (flowerLeft < 50 && flowerLeft > 0 && catTop >= 140) {
        alert("GAME OVER!!")
        location.reload()
    }
    
}, 10)

