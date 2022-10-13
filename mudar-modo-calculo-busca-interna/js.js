var result=[];


function inputp(di){
    document.getElementById("b1").style.display=di;
    
    document.getElementById("b1").focus();
}
function dark(obj){
    document.querySelector("header").classList.toggle("darkheader");
    document.body.classList.toggle("darkbody");
    divp();
}

function armval(){
   // var n=eval(nun);
//document.getElementById("meu").innerHTML=n;
var r=0;
    for(var i=0; i<=result.length-1; i++){
       r+= parseFloat(result[i],10);
        
    }

    return r;
}

function calc(obj){
  // document.getElementById("meu").innerHTML;  
//armval(obj.value+"+"+result);
     result.push(obj.value);
    if(result.length>1){ 
        document.getElementById("meu").innerHTML=armval()+"R$";
    }else{
        document.getElementById("meu").innerHTML=obj.value+"R$";
    }
    document.getElementById("clpo").style.display="block";
}
function busc(){
    var b= document.getElementById("b1").value;
    var di= document.querySelectorAll("div.plan");
    var r= document.querySelectorAll("div.plan > p");
    for(var i =0; i<=r.length-1; i++){
        if(!r[i].innerHTML.includes(b)){
           di[i].style.display="none"; 
        }else{
            di[i].style.display="inline-block";
        }
    }
}
function divp(){
	 var di= document.querySelectorAll("div.plan");
	 for(var i=0; i<=di.length; i++){
	 if(di[i].style.display=="none"){
		 console.log(i);
		 break;
		 }
	 }
}
