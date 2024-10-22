#pragma once

typedef enum hazardstype {
	spike,
}hazardstype;

typedef struct hazard {
	int x[3], y[3];
	hazardstype type;
}hazard;
