import streamlit as st
import heapq
import collections
import matplotlib.pyplot as plt
import io
import networkx as nx
import plotly.graph_objects as go

class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    def __lt__(self, other):
        return self.freq < other.freq

def huffman_encoding(text):
    if not text:
        return "", {}

    frequency = collections.Counter(text)
    heap = [[weight, Node(char, weight)] for char, weight in frequency.items()]
    heapq.heapify(heap)

    while len(heap) > 1:
        min1 = heapq.heappop(heap)
        min2 = heapq.heappop(heap)
        combined = Node(None, min1[0] + min2[0])
        combined.left = min1[1]
        combined.right = min2[1]
        heapq.heappush(heap, [combined.freq, combined])

    root = heap[0][1]
    codes = {}
    encode(root, "", codes)

    encoded_text = "".join(codes[char] for char in text)
    return encoded_text, codes, root

def encode(node, code, codes):
    if node.char:
        codes[node.char] = code
        return

    encode(node.left, code + "0", codes)
    encode(node.right, code + "1", codes)

def plot_huffman_tree(root):
    G = nx.Graph()

    def build_graph(node, parent=None, edge_label=None):
        if node.char:
            label = f"{node.char} ({node.freq})"
        else:
            label = node.freq

        G.add_node(node, label=label)

        if parent is not None:
            G.add_edge(parent, node, label=edge_label)

        if node.left:
            build_graph(node.left, node, "0")
        if node.right:
            build_graph(node.right, node, "1")

    build_graph(root)

    pos = nx.spring_layout(G, seed=42)
    node_labels = nx.get_node_attributes(G, "label")
    edge_labels = nx.get_edge_attributes(G, "label")

    fig, ax = plt.subplots(figsize=(8, 6))
    nx.draw_networkx(G, pos, with_labels=False, node_color="lightblue", node_size=800, ax=ax)
    nx.draw_networkx_labels(G, pos, labels=node_labels, font_color="black", font_size=10, ax=ax)
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color="red", font_size=8, ax=ax)
    plt.title("Huffman Tree")
    return fig

def main():
    st.title("Huffman Coding Compression")

    file = st.file_uploader("Upload a text file", type=["txt"], key="fileUploader")
    text = ""

    if file is not None:
        if file.name.endswith('.txt'):
            text = io.TextIOWrapper(file).read()
        else:
            st.error("Please upload a text file with the .txt extension.")

    if st.button("Compress") and text:
        encoded_text, codes, root = huffman_encoding(text)
        original_size = len(text.encode("utf-8"))
        compressed_size = len(encoded_text) // 8
        compression_ratio = compressed_size / original_size

        st.subheader("Huffman Tree")
        fig = plot_huffman_tree(root)
        st.pyplot(fig)

        st.subheader("Options")
        show_original_text = st.checkbox("Show Original Text")
        show_encoded_text = st.checkbox("Show Encoded Text")
        show_huffman_codes = st.checkbox("Show Huffman Codes")

        if show_original_text:
            st.subheader("Original Text")
            st.write(text)

        if show_encoded_text:
            st.subheader("Encoded Text")
            st.write(encoded_text)

        if show_huffman_codes:
            st.subheader("Huffman Codes")
            num_columns = 2
            columns = st.columns(num_columns)

            for i, (char, code) in enumerate(codes.items()):
                column_index = i % num_columns
                with columns[column_index]:
                    st.write(f"Character: {char}, Code: {code}")

        st.subheader("File Sizes")
        fig = go.Figure()
        fig.add_trace(go.Bar(x=["Original"], y=[original_size], name="Original"))
        fig.add_trace(go.Bar(x=["Compressed"], y=[compressed_size], name="Compressed"))
        fig.update_layout(
            title="Original and Compressed File Sizes",
            xaxis_title="File Type",
            yaxis_title="File Size (bytes)",
        )
        st.plotly_chart(fig)

        st.subheader("Compression Ratio")
        st.write(f"{compression_ratio:.2f}")
        
    st.subheader("Huffman Coding Compression")
    st.write("Huffman coding is a data compression algorithm that is used to encode data with variable-length codes. It is based on the concept of assigning shorter codes to more frequent characters, and longer codes to less frequent characters. This allows for efficient compression of data by reducing the overall number of bits required to represent the information.")

    st.subheader("Our Approach")
    st.write("Our approach to Huffman coding involves the following steps:")
    st.markdown("- **Frequency Calculation**: We calculate the frequency of each character in the input text.")
    st.markdown("- **Building the Huffman Tree**: We build a binary tree using a priority queue (heap) based on the character frequencies. The characters with the lowest frequencies are placed at the leaves of the tree.")
    st.markdown("- **Assigning Huffman Codes**: Starting from the root of the Huffman tree, we traverse down the tree and assign a binary code ('0' or '1') to each character. The code for each character is determined by the path from the root to the leaf node containing that character.")
    st.markdown("- **Encoding the Text**: We encode the original text using the generated Huffman codes.")
    st.markdown("- **File Size Comparison**: We compare the sizes of the original and compressed files to calculate the compression ratio.")

    st.subheader("Developer's LinkedIn Profile")
    st.markdown("[LinkedIn Profile](https://www.linkedin.com/in/talalmuzaffar)", unsafe_allow_html=True)

if __name__ == "__main__":
    main()
