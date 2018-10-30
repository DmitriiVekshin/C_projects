#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


struct zvirze
{
unsigned long int id;
unsigned long int power;
int degree;
zvirze *clone;
zvirze *sibling;
zvirze *kid;
zvirze *parent;
};

struct car
{
zvirze *max;
zvirze *min;



};
	void MinusMin( car* curCar);
	void MinusMax( car* curCar);
	void mergeMin( car* curCar);
	void mergeMax( car* curCar);
	void pripoenix( zvirze * deviant, car * temp );
	void pripoenin( zvirze * deviant, car * temp );
        void deleteclonevMin( zvirze * z);
	void deleteclonevMax( zvirze * z);
	void killBillMin ( car * curCar);
	void killBillMax ( car * curCar);
	void mergeSwap( zvirze * z1, zvirze * z2);



	void mergeMaxOn( car* curCar,zvirze*predz1,zvirze*pervni)
{
zvirze * z = pervni; 
zvirze * tmp = pervni->sibling;
zvirze * predz = predz1;
while( tmp)
{
if( tmp -> degree == z->degree )
{
	if( tmp-> power < z-> power) 
	{
	mergeSwap(z,tmp);
	}
	else if( tmp-> power > z-> power) 
	{
	if(curCar -> max == z){curCar -> max = tmp;}
	else if(predz){predz->sibling=tmp;}
	mergeSwap(tmp,z);
	}
	else
	{
	if ( tmp -> id < z -> id)
	{
	if(curCar -> max == z){curCar -> max = tmp;}
	else if(predz){predz->sibling=tmp;}
	mergeSwap(tmp,z);
	}
	else
	{
	mergeSwap(z,tmp);
	}
	}
tmp = predz1;
}
predz=z;
z = tmp;
tmp = tmp-> sibling;
}
}
void deleteclonevMin( zvirze * z)
{
zvirze * tmp1;
zvirze * tmp2;
z->power=0;
z->id=0;
while(z->parent)
{
z->power=z->parent->power;
z->id=z->parent->id;
tmp1 = z -> clone;
tmp2 = z -> parent -> clone;
z->clone=tmp2;
z->parent->clone=tmp1;
tmp1->clone=z->parent;
tmp2->clone=z;
z->clone->clone=z;
z->parent->clone->clone=z->parent;
z=z->parent;
z->id=0;
z->power=0;
}
}
void killBillMin ( car * curCar)
	{
	zvirze * z = curCar -> min ;
	zvirze * target = curCar -> min ;
	zvirze * tmp = NULL;
	zvirze * predtarget = NULL;
	while(z->sibling)
	{
        tmp=z;
	z=z->sibling;
	if(target->power>z->power)
	{
	target=z;
	predtarget=tmp;
	}
	else if ((target->power==z->power)&&(target->id>z->id))
	{
	target=z;
	predtarget=tmp;
	}
	if(target->power==0&&target->id==0){break;}
	}
if(predtarget==NULL)	
{ 
if (target->sibling)
	{
	curCar -> min=target->sibling;
	}
else
	{
	curCar -> min=NULL;
	}
}
else
{
if (target->sibling==NULL)
	{
	predtarget->sibling=NULL;
	}
else if (target->sibling)
	{
	predtarget->sibling=target->sibling;
	}
}
tmp=target->kid;
predtarget=target;
target=tmp;
while(target)
{
target=target->sibling;
pripoenin(tmp,curCar);
tmp = target;
}
}
void killBillMax ( car * curCar)
{
zvirze * z = curCar -> max ;
	zvirze * target = curCar -> max ;
	zvirze * tmp = NULL;
	zvirze * predtarget = NULL;
while(z->sibling)
	{
        tmp=z;
	z=z->sibling;
	if(target->power<z->power)
	{
	target=z;
	predtarget=tmp;
	}
	else if ((target->power==z->power)&&(target->id>z->id))
	{
	target=z;
	predtarget=tmp;
	}
		if(target->power==4294967296&&target->id==0){break;}
	}
if(predtarget==NULL)
{
if (target->sibling)
	{
	curCar -> max=target->sibling;
	}
else
	{
	curCar -> max=NULL;
	}
}
else
{
if (target->sibling==NULL)
	{
	predtarget->sibling=NULL;
	}
else if (target->sibling)
	{
	predtarget->sibling=target->sibling;
	}
}
tmp=target->kid;
predtarget=target;
target=tmp;
while(target)
{
target=target->sibling;
pripoenix(tmp,curCar);
tmp = target;
}
}

void deleteclonevMax( zvirze * z)
{
zvirze * tmp1;
zvirze * tmp2;
z->power=4294967296;
z->id=0;
while(z->parent)
{


z->power=z->parent->power;
z->id=z->parent->id;
tmp1 = z -> clone;
tmp2 = z -> parent -> clone;

z->clone=tmp2;
z->parent->clone=tmp1;
tmp1->clone=z->parent;
tmp2->clone=z;
z->clone->clone=z;
z->parent->clone->clone=z->parent;
z=z->parent;
z->id=0;
z->power=4294967296;
}
}


void fstelem ( car* tmp, unsigned long int id, unsigned long int power)
{
	tmp ->max=(zvirze*) malloc ( sizeof (zvirze) * 1 );
	tmp ->min=(zvirze*) malloc ( sizeof (zvirze) * 1 );
	tmp ->max -> id=id;
	tmp ->max -> power=power;
	tmp ->min -> id=id;
	tmp ->min -> power=power;
	tmp ->max -> clone=tmp->min;
	tmp ->min -> clone=tmp->max;
	tmp ->max -> sibling=NULL;
	tmp ->max -> parent=NULL;
	tmp ->max -> kid=NULL;
	tmp ->min -> sibling=NULL;
	tmp ->min -> parent=NULL;
	tmp ->min -> kid=NULL;
	tmp ->max -> degree=0;
	tmp ->min -> degree=0;
}
void mergeSwap( zvirze * z1, zvirze * z2){
zvirze* tmp = z1 ->kid;
if( z1 -> sibling == z2  )
{
	z1 -> sibling = z2 -> sibling;
}
z1 -> kid = z2;
z2 -> parent = z1;
z2 -> sibling = tmp;
z1 -> degree++;
}


void pripoenix( zvirze * deviant, car * temp )
{
	zvirze * fronta = temp -> max;
if(temp->max)
{

	while((fronta -> sibling)&&(fronta ->sibling->degree < deviant -> degree))
	{
	fronta = fronta -> sibling;
	}
	if(temp->max->degree>deviant -> degree)
	{
	deviant -> sibling = temp -> max;
	temp -> max = deviant;
	}
	else
	{
	deviant -> sibling = fronta -> sibling;
	fronta -> sibling = deviant;
	mergeMaxOn(temp,fronta,deviant);
	}
}
else
{
temp->max=deviant;
deviant->sibling=NULL;
}

	}

void pripoenin( zvirze * deviant, car * temp )
	{
	zvirze * fronta = temp -> min;
if(temp->min)
{

	while((fronta -> sibling)&&(fronta ->sibling->degree < deviant -> degree))
	{
	fronta = fronta -> sibling;
	}
	if(temp->min->degree>deviant -> degree)
	{
	deviant -> sibling = temp -> min;
	temp -> min = deviant;
	}
	else
	{
	deviant -> sibling = fronta -> sibling;
	fronta -> sibling = deviant;
	mergeMin(temp);
	}
}
else
{
temp->min=deviant;
deviant->sibling=NULL;
}

	}

void mergeMin( car* curCar)
{
zvirze * z = curCar -> min ; 
zvirze * tmp = curCar -> min ->sibling;
zvirze * predz=NULL;
while( tmp)
{
if( tmp -> degree == z->degree )
{
	if( tmp-> power > z-> power) 
	{
	mergeSwap(z,tmp);
	}
	else if( tmp-> power < z-> power) 
	{
	

	if(curCar -> min == z){curCar -> min = tmp;}
	else if(predz){predz->sibling=tmp;}


	mergeSwap(tmp,z);


	}
	else
	{
	if ( tmp -> id < z -> id)
	{
	if(curCar -> min == z){curCar -> min = tmp;}
	else if(predz){predz->sibling=tmp;}
	mergeSwap(tmp,z);
	}
	else
	{
	mergeSwap(z,tmp);

	}
	}
tmp = curCar -> min;
}
predz=z;
z = tmp;
tmp = tmp-> sibling;
}
}

	void MinusMin( car* curCar)
{
	zvirze * z = curCar -> min ;
	zvirze * target = curCar -> min ;
	zvirze * tmp = NULL;
	zvirze * predtarget = NULL;
if(curCar->min)
{

	while(z->sibling)
	{
        tmp=z;
	z=z->sibling;
	if(target->power>z->power)
	{
	target=z;
	predtarget=tmp;
	}
	else if ((target->power==z->power)&&(target->id>z->id))
	{
	target=z;
	predtarget=tmp;
	}
	}
printf("%lu\n",target->id);
if(predtarget==NULL)	
{ 
if (target->sibling)
	{
	curCar -> min=target->sibling;
	}
else
	{
	curCar -> min=NULL;
	}
}
else
{
if (target->sibling==NULL)
	{
	predtarget->sibling=NULL;
	}
else if (target->sibling)
	{
	predtarget->sibling=target->sibling;
	}
}
deleteclonevMax(target->clone);
killBillMax(curCar);
tmp=target->kid;
predtarget=target;
target=tmp;
while(target)
{
target->parent=NULL;
target=target->sibling;
pripoenin(tmp,curCar);
tmp = target;
}
predtarget->parent=NULL;
predtarget->sibling=NULL;
predtarget->clone=NULL;
predtarget->kid=NULL;
}
else
{
printf("empty\n");
}
}

	

	void mergeMax( car* curCar)
{
zvirze * z = curCar -> max ; 
zvirze * tmp = curCar -> max ->sibling;
zvirze * predz;
while( tmp)
{
if( tmp -> degree == z->degree )
{
	if( tmp-> power < z-> power) 
	{
	mergeSwap(z,tmp);
	}
	else if( tmp-> power > z-> power) 
	{
	if(curCar -> max == z){curCar -> max = tmp;}
	else if(predz){predz->sibling=tmp;}
	mergeSwap(tmp,z);
	}
	else
	{
	if ( tmp -> id < z -> id)
	{
	if(curCar -> max == z){curCar -> max = tmp;}
	else if(predz){predz->sibling=tmp;}
	mergeSwap(tmp,z);
	}
	else
	{
	mergeSwap(z,tmp);
	}
	}
tmp = curCar -> max;
}
predz=z;
z = tmp;
tmp = tmp-> sibling;
}
}


	void MinusMax( car* curCar)
{
	zvirze * z = curCar -> max ;
	zvirze * target = curCar -> max ;
	zvirze * tmp = NULL;
	zvirze * predtarget = NULL;
if(curCar->max)
{
	while(z->sibling)
	{
        tmp=z;
	z=z->sibling;
	if(target->power<z->power)
	{
	target=z;
	predtarget=tmp;
	}
	else if ((target->power==z->power)&&(target->id>z->id))
	{
	target=z;
	predtarget=tmp;
	}
	}
printf("%lu\n",target->id);
if(predtarget==NULL)
{
if (target->sibling)
	{
	curCar -> max=target->sibling;
	}
else
	{
	curCar -> max=NULL;
	}
}
else
{
if (target->sibling==NULL)
	{
	predtarget->sibling=NULL;
	}
else if (target->sibling)
	{
	predtarget->sibling=target->sibling;
	}
}
deleteclonevMin(target->clone);
killBillMin(curCar);
tmp=target->kid;
predtarget=target;
target=tmp;
while(target)
{
target->parent=NULL;
target=target->sibling;
pripoenix(tmp,curCar);
tmp = target;
}
predtarget->parent=NULL;
predtarget->sibling=NULL;
predtarget->clone=NULL;
predtarget->kid=NULL;
}
else
{
printf("empty\n");
}
}



void nextelem ( car* tmp, unsigned long int id, unsigned long int power)
{
	zvirze * tmp2 =(zvirze*) malloc ( sizeof (zvirze) * 1 );
	zvirze * tmp3=(zvirze*) malloc ( sizeof (zvirze) * 1 );
	tmp2 -> id=id;
	tmp2 -> power=power;
	tmp3 -> id=id;
	tmp3 -> power=power;
	tmp2 -> clone=tmp3;
	tmp3 -> clone=tmp2;
	tmp2 -> sibling=tmp->max;
	tmp3 -> sibling=tmp->min;
	tmp ->max=tmp2;
	tmp ->min=tmp3;
	tmp2 -> degree=0;
	tmp3 -> degree=0;
	tmp2 -> kid=NULL;
	tmp3 -> kid=NULL;
	tmp2 -> parent=NULL;
	tmp3 -> parent=NULL;
}

int main (void)
{
int prikaz;
unsigned long int k,id,i, power;
car* cars=(car*) malloc ( sizeof (*cars) * 10000 );
for(i=0;i<10000;i++)
{
 cars[i].min = NULL;
 cars[i].max = NULL;

}
do
{
scanf("%d",&prikaz);
if(prikaz==0)
{
	scanf("%lu %lu %lu",&k,&id,&power);
	if(cars[k].min==NULL)
	{

		fstelem(&cars[k], id , power);
	}
	else
	{
		 nextelem(&cars[k], id , power);

		mergeMin(&cars[k]);
		mergeMax(&cars[k]);
	}
}
else if(prikaz==1)
{
scanf("%lu",&k);
MinusMax(&cars[k]);
}
else if(prikaz==2)
{
scanf("%lu",&k);
MinusMin(&cars[k]);
}
else if(prikaz==3)
{
scanf("%lu%lu",&k,&k);
}
}
while ( prikaz!=4);
return 0;
}
