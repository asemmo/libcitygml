#pragma once

#include <vector>
#include <memory>

#include "parser/citygmlelementparser.h"

namespace citygml {

    /**
     * @brief The DelayedChoiceElementParser allows to parse xml elements of which the concrete type is not known in advance
     *
     * The DelayedChoiceElementParser is initialized with a list of possible parses. When the start element of the next node is parsed it chooses the
     * first parser that can handle the element.
     */
    class DelayedChoiceElementParser : public ElementParser {
    public:
        DelayedChoiceElementParser(CityGMLDocumentParser& documentParser, std::shared_ptr<CityGMLLogger> logger, std::vector<ElementParser*> choices);

        // ElementParser interface
        virtual bool startElement(const NodeType::XMLNode& node, Attributes& attributes);
        virtual bool endElement(const NodeType::XMLNode& node, const std::string& characters);
        virtual bool handlesElement(const NodeType::XMLNode& node) const;
        virtual std::string elementParserName() const;

    private:
        std::vector<ElementParser*> m_choices;
    };

}
