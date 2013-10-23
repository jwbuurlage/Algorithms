//THIS USES 1-BASED INDICES!!!! for better bitmask magic
//array of values:   f[i]
//cumulative values: c[i] = sum[ f[j] , {j,0,i} ]
//Modify values (f[i]) and read cumulative values (c[i]) both in log(n) time
//Make sure to clear tree to zero first
//http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=binaryIndexedTrees

const int MaxVal = 256;
int tree[MaxVal+1];

int read(int idx){ //returns c[i]
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

void update(int idx ,int val){ //ADDS val to f[i]
    while (idx <= MaxVal){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

void scale(int factor){ //multiplies all f[i] (and therefore c[i]) by factor
	for(int idx = 1; idx <= MaxVal; ++idx) tree[idx] *= factor;
}

// if in tree exists more than one index with a same
// cumulative frequency, this procedure will return 
// the greatest one
int find(int cumFre){
	int idx = 0;
	int bitMask = MaxVal;
	// bitMask - initialy, it is the greatest bit of MaxVal
	// bitMask store interval which should be searched
	while ((bitMask != 0) && (idx < MaxVal)){
		int tIdx = idx + bitMask;
		if (cumFre >= tree[tIdx]){ 
			idx = tIdx;
			cumFre -= tree[tIdx];
		}
		bitMask >>= 1;
	}
	if (cumFre != 0)
		return -1;
	else
		return idx;
}

//2-Dimensional
void update(int x , int y , int val){ //ADDS val to f[x,y]
	int y1;
	while (x <= max_x){
		y1 = y;
		while (y1 <= max_y){
			tree[x][y1] += val;
			y1 += (y1 & -y1); 
		}
		x += (x & -x); 
	}
}
void updatey(int x , int y , int val){
	while (y <= max_y){
		tree[x][y] += val;
		y += (y & -y); 
	}
}
