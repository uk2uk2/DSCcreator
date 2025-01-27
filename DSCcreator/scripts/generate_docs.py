const char* DOC_GENERATOR_TEMPLATE = R"(
#!/usr/bin/env python3

import os
import re
import markdown
import json
from typing import Dict, List

class DocGenerator:
    def __init__(self, src_dir: str, output_dir: str):
        self.src_dir = src_dir
        self.output_dir = output_dir
        self.api_docs = {}
        self.examples = {}
        
    def parse_header_file(self, filepath: str) -> Dict:
        """Parse a header file for documentation."""
        docs = {
            'functions': [],
            'structures': [],
            'description': ''
        }
        
        with open(filepath, 'r') as f:
            content = f.read()
            
        # Extract file description
        desc_match = re.search(r'/\*\*(.*?)\*/', content, re.DOTALL)
        if desc_match:
            docs['description'] = desc_match.group(1).strip()
            
        # Extract function documentation
        function_matches = re.finditer(
            r'/\*\*(.*?)\*/\s*([a-zA-Z_][a-zA-Z0-9_]*\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^)]*\))',
            content,
            re.DOTALL
        )
        
        for match in function_matches:
            docs['functions'].append({
                'doc': match.group(1).strip(),
                'signature': match.group(2).strip()
            })
            
        # Extract structure documentation
        struct_matches = re.finditer(
            r'/\*\*(.*?)\*/\s*typedef\s+struct\s+([a-zA-Z_][a-zA-Z0-9_]*)',
            content,
            re.DOTALL
        )
        
        for match in struct_matches:
            docs['structures'].append({
                'doc': match.group(1).strip(),
                'name': match.group(2).strip()
            })
            
        return docs
    
    def generate_api_docs(self):
        """Generate API documentation for all header files."""
        for root, _, files in os.walk(os.path.join(self.src_dir, 'include')):
            for file in files:
                if file.endswith('.h'):
                    filepath = os.path.join(root, file)
                    self.api_docs[file] = self.parse_header_file(filepath)
                    
    def generate_example_docs(self):
        """Generate documentation from example files."""
        example_dir = os.path.join(self.src_dir, 'examples')
        for file in os.listdir(example_dir):
            if file.endswith('.c'):
                with open(os.path.join(example_dir, file), 'r') as f:
                    content = f.read()
                    self.examples[file] = {
                        'code': content,
                        'description': self._extract_description(content)
                    }
                    
    def _extract_description(self, content: str) -> str:
        """Extract description from file comments."""
        desc_match = re.search(r'/\*\*(.*?)\*/', content, re.DOTALL)
        return desc_match.group(1).strip() if desc_match else ''
    
    def generate_html(self):
        """Generate HTML documentation."""
        os.makedirs(self.output_dir, exist_ok=True)
        
        # Generate API documentation
        api_content = "# API Documentation\n\n"
        for file, docs in self.api_docs.items():
            api_content += f"## {file}\n\n"
            api_content += f"{docs['description']}\n\n"
            
            if docs['structures']:
                api_content += "### Structures\n\n"
                for struct in docs['structures']:
                    api_content += f"#### {struct['name']}\n\n"
                    api_content += f"{struct['doc']}\n\n"
                    
            if docs['functions']:
                api_content += "### Functions\n\n"
                for func in docs['functions']:
                    api_content += f"#### `{func['signature']}`\n\n"
                    api_content += f"{func['doc']}\n\n"
                    
        with open(os.path.join(self.output_dir, 'api.html'), 'w') as f:
            f.write(markdown.markdown(api_content))
            
        # Generate example documentation
        example_content = "# Examples\n\n"
        for file, example in self.examples.items():
            example_content += f"## {file}\n\n"
            example_content += f"{example['description']}\n\n"
            example_content += f"```c\n{example['code']}\n```\n\n"
            
        with open(os.path.join(self.output_dir, 'examples.html'), 'w') as f:
            f.write(markdown.markdown(example_content))
            
    def generate_json(self):
        """Generate JSON documentation."""
        os.makedirs(self.output_dir, exist_ok=True)
        
        with open(os.path.join(self.output_dir, 'api.json'), 'w') as f:
            json.dump(self.api_docs, f, indent=2)
            
        with open(os.path.join(self.output_dir, 'examples.json'), 'w') as f:
            json.dump(self.examples, f, indent=2)

if __name__ == '__main__':
    generator = DocGenerator('src', 'docs')
    generator.generate_api_docs()
    generator.generate_example_docs()
    generator.generate_html()
    generator.generate_json()
)";
