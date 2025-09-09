
import json
from pathlib import Path
from pydantic import BaseModel

import logging

logger = logging.getLogger(__name__)

Id = str

Choices = dict[Id, Id]

class Node(BaseModel):
    op: Id
    children: list[Id]
    eclass: Id

class Class(BaseModel):
    nodes: list[Id]

class Egraph(BaseModel):
    nodes: dict[Id, Node | Class]
    _cached_classes: dict[Id, Class] | None = None

    # Reimplement this function from egraph-serialize:
    #
    # /// Groups the nodes in the e-graph by their e-class
    # ///
    # /// This is *only done once* and then the result is cached.
    # /// Modifications to the e-graph will not be reflected
    # /// in later calls to this function.
    # pub fn classes(&self) -> &IndexMap<ClassId, Class> {
    #     self.once_cell_classes.get_or_init(|| {
    #         let mut classes = IndexMap::new();
    #         for (node_id, node) in &self.nodes {
    #             classes
    #                 .entry(node.eclass.clone())
    #                 .or_insert_with(|| Class {
    #                     id: node.eclass.clone(),
    #                     nodes: vec![],
    #                 })
    #                 .nodes
    #                 .push(node_id.clone())
    #         }
    #         classes
    #     })
    # }
    def classes(self) -> dict[Id, Class]:
        if self._cached_classes is not None:
            return self._cached_classes

        classes: dict[Id, Class] = {}
        for node_id, node in self.nodes.items():
            if node.eclass not in classes:
                classes[node.eclass] = Class(nodes=[])
            classes[node.eclass].nodes.append(node_id)
        self._cached_classes = classes
        return self._cached_classes



def extract(egraph: Egraph) -> Choices:

    choices = {}

    for class_id, class_ in egraph.classes().items():

        # Here you would implement the logic to extract choices from the nodes
        # For now just pick any
        choices[class_id] = class_.nodes[0]

    return choices


if __name__ == "__main__":
    import argparse

    parser =argparse.ArgumentParser()
    parser.add_argument("serialized_egraph", type=Path, help="Path to the serialized egraph.")


    # If -o is present, write file to -o, otherwise use stdout.
    parser.add_argument("-o", "--output", type=Path, help="Path to write the extracted expression to. If not provided, writes to stdout.")
    args = parser.parse_args()

    output = args.output if args.output else None

    logger.info(f"Output path: {output}")

    egraph = Egraph.model_validate_json(args.serialized_egraph.read_text())

    choices = extract(egraph)

    if output:
        output.write_text(json.dumps(choices, indent=2))
    else:
        print(json.dumps(choices, indent=2))
