class Vedic < Formula
  desc "Sanskrit programming language"
  homepage "https://vedic-lang.github.io/"
  url "https://github.com/vedic-lang/vedic/archive/refs/tags/v2.0.6.tar.gz"
  sha256 "5453386fcebfa48a5f3d39bc832d19edaaaa98d8d36841428ff6a20db0dd0151"
  license "MIT"
  head "https://github.com/vedic-lang/vedic.git", branch: "main"

  livecheck do
    url :stable
    regex(/release[._-](\d+(?:\.\d+)+)/i)
    strategy :github_latest
  end

  depends_on "rust" => :build

  def install
    arch = Hardware::CPU.arm? ? "aarch64-apple-darwin" : "x86_64-apple-darwin"

    # Build for the specific architecture
    system "cargo", "build", "--release", "--package", "vedic", "--target", arch
    
    bin.install "target/#{arch}/release/vedic"
  end

  def caveats
    <<~EOS
    Vedic-lang is a Sanskrit Programming Language

    documentation here: https://vedic-lang.github.io/

      To get started, run:
        vedic --help
    EOS
  end

  test do
    # hello world in vedic
    (testpath/"hello.ved").write <<~EOS
      वद("नमस्ते विश्व!");
    EOS
    assert_match "नमस्ते विश्व!", shell_output("#{bin}/vedic hello.ved")
  end
end
