var m=-1;
let nco=0;
let produto={};
let produtos =[{
typep:"eletronico",
namep:"celular",
valor:"1000.00",
linkp:"https://www.google.com/search?client=opera&q=celular&sourceid=opera&ie=UTF-8&oe=UTF-8",
img:'imgobj/celular.jpg'

},
{
  typep:"eletronico",
  namep: "fone",
  valor:"100.00",
  linkp:"https://www.google.com/search?client=opera&q=fone&sourceid=opera&ie=UTF-8&oe=UTF-8",
  img:'imgobj/fone.jpg'
},
{
  typep:"acessorio",
  namep:"relogio",
  valor:"550.00",
  linkp:"https://www.google.com/search?client=opera&q=relogio&sourceid=opera&ie=UTF-8&oe=UTF-8",
  img:'imgobj/relogio.jpg'
}
];


window.setInterval("next()",9999);

function next(){
  document.imagens.src = produtos[m= m<(produtos.length-1) ? m+1 : 0].img;
  document.querySelector(".blo a").href=produtos[m].linkp;
}
function prev(){
  document.imagens.src = produtos[m= m>0 ? m-1 : 0].img;
  document.querySelector(".blo a").href=produtos[m].linkp 
}
function copy (){
var ori=document.querySelector(".prods");
var locopy=document.querySelector(".pro");
if(nco===0){
ori.remove();
}
for (nco; nco<=produtos.length-1; nco++){
  var copy=ori.cloneNode(true);
  locopy.appendChild(copy);
  document.querySelectorAll(".prods img")[nco].src= produtos[nco].img;
  
}
//var but = document.createElement("button");
//but.innerHTML="+";
//locopy.appendChild(but);
//console.log(nco);

}
function nobj(){
 var inp = document.querySelectorAll(".mais input");
 
  produto={
    typep:inp[0].value,
     namep:inp[1].value,
     valor:inp[2].value,
     linkp:"",
    img:inp[3].value
  }
  if(produto.typep!=""){
  produtos.push(produto);
  copy();
  }
}

function nextscroll(){
  document.querySelector(".pro").scrollLeft+=95;
}
function prevscroll(){
  document.querySelector(".pro").scrollLeft-=100;
}
function db(nb){
  document.querySelector(".mais").style.display=nb;
}
function imp(nb,nb2){
 
  var imp=document.querySelectorAll("header input");
  imp[0].style.display=nb;
  imp[1].style.display='block';
  document.querySelector("header button").style.display=nb2;
  if(nb!='none')
  imp[0].focus();

}

function load() {
  var el = document.querySelectorAll("input[type='text']");
  console.log(el[1]);
  for(var i=0; i<=el.length-1; i++){
  el[i].addEventListener("click",function (){
    this.select();
    
  });
}
}


document.addEventListener("DOMContentLoaded", load)

//console.log(produtos[0].name);
//console.log(produtos.find(produtos => "eletronico" === produtos.type));
//console.log(produtos.filter(produtos => "eletronico" === produtos.type));








