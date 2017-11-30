#include "proct2.hpp";
ImageLoader::ilError(uint code){
	switch(code){
		case 0:
			fprintf(stderr,"ImageLoader:Erro, não foi possível alocar memória para imagem\n");
			exit(127);
			break;
		case 1:
		
			break;
		case 2:
			break;
		case 3:
			fprintf(stderr,"ImageLoader:Erro, argumento inválido\n");
			exit(127);
		case 4:
			fprintf(stderr,"ImageLoader:Erro, impossível realizar mesma função duas vezes\n");
			exit(127);
		case 5:
			fprintf(stderr,"ImageLoader:Erro, somente uma função de limiar possível\n");
			exit(127);
	}
}
ImageLoader::ImageLoader(){
	isShapeSet=false;
	isThreshSet=false;
	dsIndex=0;
}
void ImageLoader::addParam(IcParamCode p,std::vector<int> args){
	paramArgs.push_back(args);
	size_t noParams=params.size();
	if(p>IL_MAX_ARG_CODE)ilError(3);
	for(uint i=0;i<noParams;i++)if(params[i]==p)ilError(4);
	if(p<=ILHUMOMENTS_SHA){//if param is shape
		isShapeSet=true;
	}
	params.push_back(p);
}
void ImageLoader::setThresh(ThreshCode p,std::vector<int> args){
	if(isThreshSet)ilError(5);
	isThreshSet=true;
	tparam=p;
	targs=args;
}
void ImageLoader::addImage(const char* filename{
	size_t noParams=params.size();
	ds->push_back(NULL);//Not sure
	currentData=ds[dsIndex].data;
	Image im,tim,eim;
	im=getImage(filename);
	if(im.data==NULL)return;
	if(isThreshSet){
		switch(tparam){
			case ILSIMPLE_THR:
				tim=simple_threshold(&im);
				break;
			case ILKMEAN_THR:
				tim=kmean_threshold(&im);
				break;
		}
		eim=binEdgeDetect(&tim);
	}

	for(uint i=0;i<noParams;i++){
		switch(params[i]){
			case ILFOURIER_SHA:
				fourier_shape(&tim);
				break;
			case ILFRACTDIM_SHA:
				fractdim_shape(&tim);
				break;
			case ILHUMOMENTS_SHA:
				humoments_shape(&tim);
				break;
			case ILFOURIER_TEX:
				fourier_texture(&im);
				break;
			case ILFRACTDIM_TEX:
				fractdim_texture(&im);
				break;
			case ILLBP_TEX:
				lbp_texture(&im);
				break;
		}
	}
	dsIndex++;
}
