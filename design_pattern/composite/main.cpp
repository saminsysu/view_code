#include "composite.h"
#include "leaf.h"

int main() {
	Component *component;
	Component *leaf1 = new Leaf("leaf1");
	Component *leaf2 = new Leaf("leaf2");
	Component *leaf3 = new Leaf("leaf3");

	Component *composite = new Composite("composite");
	Component *subcomposite1 = new Composite("subcomposite1");
	Component *subcomposite2 = new Composite("subcomposite2");
	Component *subsubcomposite = new Composite("subsubcomposite");

	composite -> add(leaf1);

	composite -> add(subcomposite1);

	subcomposite1 -> add(subsubcomposite);

	subsubcomposite -> add(leaf3);

	composite -> add(subcomposite2);

	subcomposite2 -> add(leaf2);

	composite -> show();

	composite -> remove(leaf1);

	composite -> show();

	composite -> remove(subcomposite1);

	leaf3 = nullptr;

	composite -> show();

	safe_delete(leaf2);

	return 0;
}