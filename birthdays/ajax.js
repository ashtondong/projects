function async()
{
    let submit = document.querySelector('#submit');

    submit.addEventListener('clicked', function(){

        var ajax = new XMLHttpRequest();

        ajax.onreadystatechange = function(){
            if (ajax.readyState == 4 && ajax.status == 200) {
                $('#info').html(ajax.responseText);
            };
        };

        ajax.open('GET', index.html, true);
        ajax.send();
    });

/* This doesn't work. But the idea is to have the page load asynchronously after a birthday is submitted */

}